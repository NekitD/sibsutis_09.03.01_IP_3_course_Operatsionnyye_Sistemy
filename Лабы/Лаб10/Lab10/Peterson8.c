#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int sum = 0, sum1 = 0, sum2 = 0, i = 0, j = 0, op_counter_1 = 1, op_counter_2 = 1;
int array[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};



//------------ПЕТЕРСОН-----------------------------------------------------------------------
int turn = 0, flagReady[2] = {1, 1};

void* thread_1(){
    for(i = 0; i < 10; i++){
        flagReady[0] = 1;
        turn = 1;
        while(turn == 1 && flagReady[1] == 1){
            usleep(1000);
        };
        sum1 += array[i];
        printf("Поток 1, Операция %d: %d\n", op_counter_1, sum1);
        flagReady[0] = 0;
        usleep(1);
        op_counter_1++;
        usleep(1000);
    }
}

void* thread_2(){
    for(j = 10; j < 20; j++){
        flagReady[1] = 1;
        turn = 0;
        while(turn == 0 && flagReady[0] == 1){
            usleep(1000);
        };
        sum2 += array[j];
        printf("Поток 2, Операция %d: %d\n", op_counter_2, sum2);
        flagReady[1] = 0;
        usleep(1);
        op_counter_2++;
        usleep(10);
    }
}

//-----------------------------------------------------------------------

int main(){
    printf("PTHREADS:\n");

    pthread_t th_id[2];
    pthread_create(&th_id[0], NULL, &thread_1, NULL);
    pthread_create(&th_id[1], NULL, &thread_2, NULL);
    pthread_join(th_id[0], NULL);
    pthread_join(th_id[1], NULL);
    
    printf("\nФинальная операция: %i + %i\n",sum1, sum2);
    sum = sum1 + sum2;
    printf("\nКонечная сумма = %i\n",sum);

    return 0;
}