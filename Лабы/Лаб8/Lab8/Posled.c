#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>


int main(){
    int sum = 0, i = 0, op_counter = 1;
    int array[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    struct timeval t0, t1;
    gettimeofday(&t0, NULL);
    printf("ПОСЛЕДОВАТЕЛЬНЫЙ КОД:\n");
    for(i = 0; i < 20; i++){
        sum += array[i];
        printf("Операция %d: %d\n", op_counter, sum);
        usleep(1);
        op_counter++;
    }
    gettimeofday(&t1, NULL);
    printf("\nКонечная сумма = %d\n", sum);

    //-------------------------------------------------------------------

    long long et0 = (t0.tv_sec * 1000000LL) + t0.tv_usec;
    long long et1 = (t1.tv_sec * 1000000LL) + t1.tv_usec;
    long long time_us = et1 - et0;
    
    printf("\nВремя выполнения: %lld микросекунд\n", time_us);
    printf("Время выполнения: %.6f миллисекунд\n", time_us / 1000.0);
    printf("Время выполнения: %.9f секунд\n", time_us / 1000000.0);

    return 0;
}