#include <stdio.h>
#include <pthread.h>

void *busy(void *ptr) {
    puts("Hello World");
    return NULL;
}

void *busy2(void *ptr) {
    puts("I <3 Linux");
    return NULL;
}

int main() {
    pthread_t id;
    pthread_create(&id, NULL, busy, "Hi");
    pthread_create(&id, NULL, busy2, "Hey");
    while(1){}
}
