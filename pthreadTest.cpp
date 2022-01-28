
#include <pthread.h>
#include <iostream>

using namespace std;

void *busy(void *ptr) {
    puts("Hello World");
    return NULL;
}

int main() {
    pthread_t id;
    pthread_create(&id, NULL, busy, (void *)"Hi");
    while(1){}
    
    return 0;
}
