#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <malloc.h>
#include <semaphore.h>

#define MAX_BUFFER_SIZE 100

typedef struct port{
    struct port* next;
} portion;

void* producer(void*);
void* consumer(void*);

portion* buffer = NULL;
pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t buffer_size;
sem_t empty_slots; 
int production_count = 0;
int producer_finished = 0;

int main(){
    int i;
    sem_init(&buffer_size, 0, 0);
    sem_init(&empty_slots, 0, MAX_BUFFER_SIZE);
    
    pthread_t producer_id, consumer_id[3];
    pthread_create(&producer_id, NULL, &producer, NULL);
    for(i = 0; i < 3; i++){
        pthread_create(&consumer_id[i], NULL, &consumer, NULL);
    }

    pthread_join(producer_id, NULL);
    for(i = 0; i < 3; i++){
        pthread_join(consumer_id[i], NULL);
    }

    sem_destroy(&buffer_size);
    sem_destroy(&empty_slots);
    pthread_mutex_destroy(&Mutex);

    return 0;
}

void* producer(void* params){
    while(1){
        if(production_count++ > 200) break;
        usleep(100);
        
        portion* new_portion = (portion*)calloc(1, sizeof(portion));
        if (!new_portion) {
            perror("Failed to allocate portion");
            break;
        }

        sem_wait(&empty_slots);
        pthread_mutex_lock(&Mutex);
        
        new_portion->next = buffer;
        buffer = new_portion;
        
        pthread_mutex_unlock(&Mutex);
        sem_post(&buffer_size);

    }
    
    pthread_mutex_lock(&Mutex);
    producer_finished = 1;
    pthread_mutex_unlock(&Mutex);
    
    for(int i = 0; i < 3; i++) {
        sem_post(&buffer_size);
    }
    
    return NULL;
}

void* consumer(void* params){
    while(1){
        sem_wait(&buffer_size);
        
        pthread_mutex_lock(&Mutex);
        
        if (producer_finished && buffer == NULL) {
            pthread_mutex_unlock(&Mutex);
            break;
        }
        
        portion* next_portion = buffer;
        if (buffer != NULL) {
            buffer = buffer->next;
        }
        
        pthread_mutex_unlock(&Mutex);
        
        if (next_portion != NULL) {
            printf("Consumed: %p\n", (void*)next_portion);
            free(next_portion);
            sem_post(&empty_slots);
        } else {
            sem_post(&buffer_size);
        }
    }
    return NULL;
}