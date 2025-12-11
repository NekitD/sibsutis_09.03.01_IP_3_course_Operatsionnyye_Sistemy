#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

void print_elf_header_info(Elf64_Ehdr *header) {
    printf("=== ELF Header Information ===\n");
    printf("Magic: %02x %02x %02x %02x\n",
           header->e_ident[EI_MAG0], header->e_ident[EI_MAG1],
           header->e_ident[EI_MAG2], header->e_ident[EI_MAG3]);
    printf("Class: %d (%s)\n", header->e_ident[EI_CLASS],
           header->e_ident[EI_CLASS] == ELFCLASS64 ? "64-bit" : "32-bit");
    printf("Type: %d\n", header->e_type);
    printf("Machine: %d\n", header->e_machine);
    printf("Version: %d\n", header->e_version);
    printf("Entry point: 0x%lx\n", header->e_entry);
    printf("Program header offset: %lu\n", header->e_phoff);
    printf("Section header offset: %lu\n", header->e_shoff);
    printf("Section header string table index: %d\n", header->e_shstrndx);
    printf("Number of section headers: %d\n", header->e_shnum);
    printf("Size of section headers: %d\n", header->e_shentsize);
    printf("\n");
}

void print_program_headers(const char* elfFile, Elf64_Ehdr *header) {
    printf("=== Program Headers ===\n");

    int fd = open(elfFile, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }

    lseek(fd, header->e_phoff, SEEK_SET);

    for(int i = 0; i < header->e_phnum; i++) {
        Elf64_Phdr phheader;
        read(fd, &phheader, header->e_phentsize);

        printf("Header %d:\n", i);
        printf("  Type: %x\n", phheader.p_type);
        printf("  Offset: 0x%lx\n", phheader.p_offset);
        printf("  Virtual Address: 0x%lx\n", phheader.p_vaddr);
        printf("  Physical Address: 0x%lx\n", phheader.p_paddr);
        printf("  File Size: 0x%lx\n", phheader.p_filesz);
        printf("  Memory Size: 0x%lx\n", phheader.p_memsz);
        printf("  Flags: %x ", phheader.p_flags);

        // Расшифровка флагов
        if (phheader.p_flags & PF_R) printf("R");
        if (phheader.p_flags & PF_W) printf("W");
        if (phheader.p_flags & PF_X) printf("X");
        printf("\n  Align: 0x%lx\n\n", phheader.p_align);
    }

    close(fd);
}

//-----------------------------------------------------------------------------------

void print_section_names(const char* elfFile, Elf64_Ehdr *header) {
    printf("Имена разделов:\n");

    int fd = open(elfFile, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }

    if (header->e_shstrndx == SHN_UNDEF) {
        printf("Section header string table index is undefined\n");
        close(fd);
        return;
    }

    Elf64_Shdr shstrtab_header;
    lseek(fd, header->e_shoff + header->e_shstrndx * header->e_shentsize, SEEK_SET);
    read(fd, &shstrtab_header, sizeof(Elf64_Shdr));

    char *shstrtab = malloc(shstrtab_header.sh_size);
    lseek(fd, shstrtab_header.sh_offset, SEEK_SET);
    read(fd, shstrtab, shstrtab_header.sh_size);

    printf("Section header string table at offset: 0x%lx, size: %lu\n",
           shstrtab_header.sh_offset, shstrtab_header.sh_size);
    printf("\n");

    lseek(fd, header->e_shoff, SEEK_SET);

    for(int i = 0; i < header->e_shnum; i++) {
        Elf64_Shdr section_header;
        read(fd, &section_header, header->e_shentsize);

        const char *section_name = shstrtab + section_header.sh_name;

        printf("Section [%2d]: %-20s\n", i, section_name);
        printf("  Type: 0x%x, Flags: 0x%lx, Offset: 0x%lx, Size: %lu\n",
               section_header.sh_type, section_header.sh_flags,
               section_header.sh_offset, section_header.sh_size);
    }

    free(shstrtab);
    close(fd);
    printf("\n");
}

void print_symbol_table(const char* elfFile, Elf64_Ehdr *header) {
    printf("=== Symbol Table ===\n");

    int fd = open(elfFile, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }

    Elf64_Shdr symtab_header, strtab_header;
    int symtab_found = 0, strtab_found = 0;

    lseek(fd, header->e_shoff, SEEK_SET);

    for(int i = 0; i < header->e_shnum; i++) {
        Elf64_Shdr section_header;
        read(fd, &section_header, header->e_shentsize);

        Elf64_Shdr shstrtab_header;
        lseek(fd, header->e_shoff + header->e_shstrndx * header->e_shentsize, SEEK_SET);
        read(fd, &shstrtab_header, sizeof(Elf64_Shdr));

        char section_name[32];
        lseek(fd, shstrtab_header.sh_offset + section_header.sh_name, SEEK_SET);
        read(fd, section_name, sizeof(section_name) - 1);
        section_name[31] = '\0';

        if (strcmp(section_name, ".dynsym") == 0) {
            symtab_header = section_header;
            symtab_found = 1;
        } else if (strcmp(section_name, ".dynstr") == 0) {
            strtab_header = section_header;
            strtab_found = 1;
        }
    }

    if (!symtab_found || !strtab_found) {
        printf("Symbol table or string table not found\n");
        close(fd);
        return;
    }

    printf("Symbol table entries:\n");
    for(int i = 0; i < symtab_header.sh_size / symtab_header.sh_entsize; i++) {
        Elf64_Sym symbol;
        lseek(fd, symtab_header.sh_offset + i * symtab_header.sh_entsize, SEEK_SET);
        read(fd, &symbol, sizeof(Elf64_Sym));

        char symbol_name[64];
        lseek(fd, strtab_header.sh_offset + symbol.st_name, SEEK_SET);
        int bytes_read = read(fd, symbol_name, sizeof(symbol_name) - 1);
        symbol_name[bytes_read] = '\0';

        if (symbol.st_name != 0) {
            printf("  %-30s Value: 0x%lx, Size: %lu, Type: %d\n",
                   symbol_name, symbol.st_value, symbol.st_size,
                   ELF64_ST_TYPE(symbol.st_info));
        }
    }

    close(fd);
    printf("\n");
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <elf_file>\n", argv[0]);
        printf("Example: %s liblist.so\n", argv[0]);
        return 1;
    }

    const char* elfFile = argv[1];

    int fd = open(elfFile, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    Elf64_Ehdr header;
    read(fd, &header, sizeof(Elf64_Ehdr));
    close(fd);

    if (memcmp(header.e_ident, ELFMAG, SELFMAG) != 0) {
        printf("This is not an ELF file!\n");
        return 1;
    }

    printf("Sections of: %s\n\n", elfFile);

    print_elf_header_info(&header);
    print_program_headers(elfFile, &header);
    print_section_names(elfFile, &header);
    print_symbol_table(elfFile, &header);

    printf("\n\n");

    return 0;
}
