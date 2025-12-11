#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

char sh[6];
int run = 1;
int counter = 0;
volatile int turn = 0;
volatile int data_ready = 0;

void* Thread1(void* pParams);
void* Thread2(void* pParams);

int main(void)
{
    pthread_t thread_id1, thread_id2;
    int r_count = 0;
    pthread_create(&thread_id1, NULL, &Thread1, NULL);
    pthread_create(&thread_id2, NULL, &Thread2, NULL);

    while(run && r_count < 20){
        while(!data_ready && run) {
            usleep(1000);
        }
        
        if (data_ready) {
            printf("%s\n", sh);
            r_count++;
            data_ready = 0;
        }
    }

    run = 0;
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    return 0;
}

void* Thread1(void* pParams){
    while(run){
        while(turn != 0 && run) {
            usleep(1000);
        }
        
        if (!run) break;
        
        sh[0] = 'H';
        sh[1] = 'e';
        sh[2] = 'l';
        sh[3] = 'l';
        sh[4] = 'o';
        sh[5] = '\0';
        counter++;
        
        data_ready = 1;
        
        while(data_ready && run) {
            usleep(1000);
        }
        turn = 1;
    }
    return NULL;
}

void* Thread2(void* pParams){
    while(run){
        while(turn != 1 && run) {
            usleep(1000);
        }
        
        if (!run) break;
        
        sh[0] = 'B';
        sh[1] = 'y';
        sh[2] = 'e';
        sh[3] = '_';
        sh[4] = 'u';
        sh[5] = '\0';
        counter++;
        
        data_ready = 1;
        
        while(data_ready && run) {
            usleep(1000);
        }
        
        turn = 0;
    }
    return NULL;
}