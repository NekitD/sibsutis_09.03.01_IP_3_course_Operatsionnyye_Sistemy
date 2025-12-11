#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

int main() {
    struct stat stat_file;
    char* map_address;
    int fd;
    
    fd = open("test_shared.txt", O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "open failed\n");
        return 1;
    }
    
    map_address = (char*)mmap(0, 256, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map_address == MAP_FAILED) {
        fprintf(stderr, "mmap failed\n");
        close(fd);
        return 1;
    }
    
    printf("Reader: Message from shared memory: %s\n", map_address);
    
    printf("Press Enter to exit...");
    getchar();
    
    munmap(map_address, 256);
    close(fd);
    
    return 0;
}