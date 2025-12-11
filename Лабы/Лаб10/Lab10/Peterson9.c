#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

char sh[6] = "INIT:";
int run = 1;
int counter = 0;
volatile int turn = 0;
volatile int data_ready = 0;

void* Thread1(void* pParams);
void* Thread2(void* pParams);

void set_affinity(int core) {
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(core, &set);
    
    if (pthread_setaffinity_np(pthread_self(), sizeof(set), &set) != 0) {
        printf("Ошибка установки affinity для ядра %d\n", core);
    }
}


void print_affinity(const char* thread_name) {
    cpu_set_t set;
    CPU_ZERO(&set);
    
    if (pthread_getaffinity_np(pthread_self(), sizeof(set), &set) == 0) {
        printf("%s работает на ядрах: ", thread_name);
        for (int i = 0; i < CPU_SETSIZE; i++) {
            if (CPU_ISSET(i, &set)) {
                printf("%d ", i);
            }
        }
        printf("\n");
    }
}

int main(int argc, char* argv[])
{
    int num_cores = 1;
    
    if (argc > 1) {
        num_cores = atoi(argv[1]);
        if (num_cores < 1 || num_cores > 3) {
            printf("Использование: %s <количество_ядер: 1-3>\n", argv[0]);
            return 1;
        }
    }
    
    printf("ТЕСТ НА %d ЯДРАХ:\n", num_cores);
    
    pthread_t thread_id1, thread_id2;
    int r_count = 0;
    

    pthread_create(&thread_id1, NULL, &Thread1, (void*)(long)num_cores);
    pthread_create(&thread_id2, NULL, &Thread2, (void*)(long)num_cores);

    set_affinity(0);
    print_affinity("Main поток");

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
    int num_cores = (int)(long)pParams;
    
    if (num_cores == 1) {
        set_affinity(0);  
    } else if (num_cores == 2) {
        set_affinity(0);  
    } else if (num_cores == 3) {
        set_affinity(1);
    }
    
    print_affinity("Поток 1");
    
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
    int num_cores = (int)(long)pParams;
    
    if (num_cores == 1) {
        set_affinity(0);
    } else if (num_cores == 2) {
        set_affinity(1);
    } else if (num_cores == 3) {
        set_affinity(2);
    }
    
    print_affinity("Поток 2");
    
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