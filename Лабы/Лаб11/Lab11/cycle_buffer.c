#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <malloc.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

typedef struct port{
    struct port* next;
} portion;

typedef struct buf {
    portion* data[BUFFER_SIZE];
    int head;
    int tail;
    int count;
} c_buffer;

void* producer(void*);
void* consumer(void*);

c_buffer buffer = {0};
pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t buffer_size;
sem_t empty_slots;  
int production_count = 0; 
int producer_finished = 0;  

int main(){
    int i;
    sem_init(&buffer_size, 0, 0);
    sem_init(&empty_slots, 0, BUFFER_SIZE); 
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
        
        buffer.data[buffer.head] = new_portion;
        buffer.head = (buffer.head + 1) % BUFFER_SIZE;
        buffer.count++;
        
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
        
        
        if (producer_finished && buffer.count == 0) {
            pthread_mutex_unlock(&Mutex);
            break;
        }
        
        
        portion* next_portion = buffer.data[buffer.tail];
        buffer.data[buffer.tail] = NULL;
        buffer.tail = (buffer.tail + 1) % BUFFER_SIZE;
        buffer.count--;
        
        pthread_mutex_unlock(&Mutex);
        sem_post(&empty_slots);
        
        printf("Consumed: %p\n", next_portion);
        free(next_portion);
    }
    return NULL;
}