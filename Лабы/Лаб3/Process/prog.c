#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void parent(pid_t child_pid){
    fprintf(stdout, "I'm the Parent: My ID is %i\n", (int)getpid(), (int)child_pid);
}

void child(pid_t parent_pid){
    fprintf(stdout, "I'm the Child. My ID is %i\n", (int)getpid());
}

int main(){
    pid_t parent_id = getpid();
    pid_t child_id;
    int i = 0;
    
    fprintf(stdout, "Parent process started, ID is %i\n", (int)parent_id);
    
    child_id = fork();
    
    if (child_id == -1) {
        perror("fork failed");
        return 1;
    }
    
    while (1) {
        if (child_id != 0) {
            parent(child_id);
        } else {
            child(parent_id);
        }
        sleep(1); 
    }
    
    return 0;
}
