#include <iostream>
#include <unistd.h>
#include <mutex>

using namespace std;

int n = 10;
mutex mtx;
int full = 0;
int empty = n;

void produce() {
    while(1) {
        mtx.lock();

        if(full < n) {
            wait(empty);
            signal(full);
        }
    }
}

int main() {



    return 0;
}

void wait(int semaphore) {
    semaphore--;
}

void signal(int semaphore) {
    semaphore++;
}