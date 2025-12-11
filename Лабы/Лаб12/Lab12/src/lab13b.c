#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int main(int argc, char* const argv[]) {
    struct stat stat_file;
    char dummy;
    char* map_address;
    int fd;
    
    fd = open("test.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
    if (fd == -1) {
        fprintf(stderr, "open failed\n");
        return 1;
    }
    
    write(fd, "This is a test", 14);
    
    if (fstat(fd, &stat_file) == -1) {
        fprintf(stderr, "stat failed\n");
        close(fd);
        return 1;
    }
    
    map_address = (char*)mmap(0, stat_file.st_size, 
                             PROT_READ | PROT_WRITE,
                             MAP_PRIVATE, fd, 0);
    if (map_address == MAP_FAILED) {
        fprintf(stderr, "mmap failed\n");
        close(fd);
        return 1;
    }
    
    printf("Original: %s\n", map_address);
    
    dummy = map_address[1];
    map_address[0] = map_address[5] - 0x20;
    map_address[1] = map_address[3];
    map_address[2] = map_address[4];
    map_address[3] = map_address[10];
    map_address[4] = dummy;
    map_address[14] = '?';
    
    printf("Modified: %s\n", map_address);
    
    msync(map_address, stat_file.st_size, MS_SYNC);
    
    munmap(map_address, stat_file.st_size);
    close(fd);
    
    return 0;
}