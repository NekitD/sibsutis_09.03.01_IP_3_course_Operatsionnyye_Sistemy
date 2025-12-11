#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

char sh[6];

atomic<bool> run{true};
atomic<bool> data_ready{false};

atomic<int> readyFlags[2] = {0, 0};
atomic<int> turn{0};

//Модель упорядочивания
constexpr memory_order MEM_ORDER = memory_order_seq_cst;

// memory_order_seq_cst
// memory_order_acq_rel
// memory_order_release
// memory_order_acquire
// memory_order_relaxed 

void EnterCriticalRegion(int threadId) {
    int x = 1;
    int y = 1 - threadId;
    
    readyFlags[threadId].store(x, MEM_ORDER);
    turn.store(y, MEM_ORDER);
    
    while (turn.load(MEM_ORDER) == (1 - threadId) && readyFlags[1 - threadId].load(MEM_ORDER) == 1) {
        this_thread::yield();
    }
}

void LeaveCriticalRegion(int threadId) {
    int x = 0;
    readyFlags[threadId].store(x, MEM_ORDER);
}

void Thread1() {
    int id = 0;
    while (run.load(memory_order_relaxed)) {
        EnterCriticalRegion(id);
        
        if (!run.load(memory_order_relaxed)) {
            LeaveCriticalRegion(id);
            break;
        }
        
        sh[0] = 'H';
        sh[1] = 'e';
        sh[2] = 'l'; 
        sh[3] = 'l'; 
        sh[4] = 'o'; 
        sh[5] = '\0';
        
        data_ready.store(true, memory_order_release);
        while (data_ready.load(memory_order_acquire) && run.load(memory_order_relaxed)) {
            this_thread::yield();
        }
        
        LeaveCriticalRegion(id);
    }
}

void Thread2() {
    int id = 1;
    while (run.load(memory_order_relaxed)) {
        EnterCriticalRegion(id);
        
        if (!run.load(memory_order_relaxed)) {
            LeaveCriticalRegion(id);
            break;
        }
        
        sh[0] = 'B'; 
        sh[1] = 'y'; 
        sh[2] = 'e';
        sh[3] = '_'; 
        sh[4] = 'u'; 
        sh[5] = '\0';
        
        data_ready.store(true, memory_order_release);
        while (data_ready.load(memory_order_acquire) && run.load(memory_order_relaxed)) {
            this_thread::yield();
        }
        
        LeaveCriticalRegion(id);
    }
}

int main() {
    thread t1(Thread1);
    thread t2(Thread2);
    
    int r_count = 0;
    
    while (run && r_count < 20) {
        while (!data_ready.load(memory_order_acquire) && run) {
            this_thread::sleep_for(chrono::milliseconds(1));
        }
        
        if (data_ready.load(memory_order_acquire)) {
            cout << sh << endl;
            r_count++;
            data_ready.store(false, memory_order_release);
        }
    }
    
    run.store(false);
    t1.join();
    t2.join();
    
    return 0;
}