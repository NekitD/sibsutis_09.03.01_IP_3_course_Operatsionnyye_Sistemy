#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/shm.h>

int main() {
    char* map_address;
    int fd;
    
    fd = shm_open("/common_region", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
    if (fd == -1) {
        perror("shm_open failed");
        return 1;
    }
    
    ftruncate(fd, 256);
    
    map_address = (char*)mmap(0, 256, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map_address == MAP_FAILED) {
        perror("mmap failed");
        close(fd);
        return 1;
    }
    
    close(fd);
    
    strcpy(map_address, "Take it easy! Be happy!");
    printf("Writer: Written message to POSIX shared memory\n");
    
    printf("Press Enter to exit and unlink...");
    getchar();
    
    munmap(map_address, 256);
    shm_unlink("/common_region");
    
    return 0;
}