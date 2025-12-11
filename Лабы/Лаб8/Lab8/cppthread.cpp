#include <iostream>
#include <thread>
#include <unistd.h>
#include <sys/time.h>

using namespace std;


int sum = 0, sum1 = 0, sum2 = 0, op_counter_1 = 1, op_counter_2 = 1;
int arr[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};


void* thread_1(){
    for(int i = 0; i < 10; i++){
        sum1 += arr[i];
        cout << "Поток 1, Операция " << op_counter_1 <<": " << sum1 << endl;
        usleep(1);
        op_counter_1++;
    }
    return 0;
}

void* thread_2(){
    for(int j = 10; j < 20; j++){
        sum2 += arr[j];
        cout << "Поток 2, Операция " << op_counter_2 <<": " << sum2 << endl;
        usleep(1);
        op_counter_2++;
    }
    return 0;
}

int main(){
    cout << "C++11 <thread>:" << endl;
    struct timeval t0, t1;

    thread th1(thread_1);
    thread th2(thread_2);
    gettimeofday(&t0, NULL);
    th1.join();
    th2.join();
    
    cout << endl << "Финальная операция: " << sum1 << " + " << sum2 << endl;
    sum = sum1 + sum2;
    gettimeofday(&t1, NULL);
    cout << endl << "Конечная сумма = " << sum << endl;

    //-------------------------------------------------------------------

    long long et0 = (t0.tv_sec * 1000000LL) + t0.tv_usec;
    long long et1 = (t1.tv_sec * 1000000LL) + t1.tv_usec;
    long long time_us = et1 - et0;
    
    printf("\nВремя выполнения: %lld микросекунд\n", time_us);
    printf("Время выполнения: %.6f миллисекунд\n", time_us / 1000.0);
    printf("Время выполнения: %.9f секунд\n", time_us / 1000000.0);

    return 0;
}