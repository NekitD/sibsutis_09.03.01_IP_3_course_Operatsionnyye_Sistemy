#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3;

    printf("Root process PID: %d\n", getpid());

    pid1 = fork(); //	1

    if (pid1 == 0) {
        printf("Child 1: PID=%d, Parent PID=%d\n", getpid(), getppid());

        pid2 = fork(); //	2

        if (pid2 == 0) {
            printf("Grandchild: PID=%d, Parent PID=%d\n", getpid(), getppid());
            sleep(120);
            exit(0);
        } else {
            sleep(120);
            wait(NULL);
            exit(0);
        }
    } else {
        pid3 = fork(); //	1

        if (pid3 == 0) {
            printf("Child 2: PID=%d, Parent PID=%d\n", getpid(), getppid());
            sleep(120);
            exit(0);
        } else {
            printf("Parent waiting...\n");
            sleep(60);

            wait(NULL);
            wait(NULL);
            printf("All children finished\n");
        }
    }

    return 0;
}
