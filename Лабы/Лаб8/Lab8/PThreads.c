#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

int sum = 0, sum1 = 0, sum2 = 0, i = 0, j = 0, op_counter_1 = 1, op_counter_2 = 1;
int array[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

void* thread_1(){
    for(i = 0; i < 10; i++){
        sum1 += array[i];
        printf("Поток 1, Операция %d: %d\n", op_counter_1, sum1);
        usleep(1);
        op_counter_1++;
        usleep(1000);
    }
}

void* thread_2(){
    for(j = 10; j < 20; j++){
        sum2 += array[j];
        printf("Поток 2, Операция %d: %d\n", op_counter_2, sum2);
        usleep(1);
        op_counter_2++;
        usleep(10);
    }
}

int main(){
    printf("PTHREADS:\n");
    struct timeval t0, t1;
    pthread_t th_id[2];
    pthread_create(&th_id[0], NULL, &thread_1, NULL);
    pthread_create(&th_id[1], NULL, &thread_2, NULL);
    gettimeofday(&t0, NULL);
    pthread_join(th_id[0], NULL);
    pthread_join(th_id[1], NULL);
    
    printf("\nФинальная операция: %i + %i\n",sum1, sum2);
    sum = sum1 + sum2;
    gettimeofday(&t1, NULL);
    printf("\nКонечная сумма = %i\n",sum);

    //-------------------------------------------------------------------

    long long et0 = (t0.tv_sec * 1000000LL) + t0.tv_usec;
    long long et1 = (t1.tv_sec * 1000000LL) + t1.tv_usec;
    long long time_us = et1 - et0;
    
    printf("\nВремя выполнения: %lld микросекунд\n", time_us);
    printf("Время выполнения: %.6f миллисекунд\n", time_us / 1000.0);
    printf("Время выполнения: %.9f секунд\n", time_us / 1000000.0);

    return 0;
}