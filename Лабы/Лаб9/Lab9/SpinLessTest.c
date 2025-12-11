#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

char sh[6];
int run = 1;
int counter = 0;

void* Thread1(void* pParams);
void* Thread2(void* pParams);

int main(void)
{
    pthread_t thread_id1, thread_id2;
    int r_count = 0;
    pthread_create(&thread_id1, NULL, &Thread1, NULL);
    pthread_create(&thread_id2, NULL, &Thread2, NULL);

    while(run && r_count < 20){
        printf("%s\n", sh);
        r_count++;
        usleep(2);
    }

    run = 0;
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    return 0;
}

void* Thread1(void* pParams){
    while(run){
        if(counter%2){
            sh[0] = 'H';
            sh[1] = 'e';
            sh[2] = 'l';
            sh[3] = 'l';
            sh[4] = 'o';
            sh[5] = '\0';
            counter++;
            usleep(1);
        }
    }
    return NULL;
}

void* Thread2(void* pParams){
    while(run){
        if(!(counter%2)){
            sh[0] = 'B';
            sh[1] = 'y';
            sh[2] = 'e';
            sh[3] = '_';
            sh[4] = 'u';
            sh[5] = '\0';
            counter++;
            usleep(1);
        }
    }
    return NULL;
}