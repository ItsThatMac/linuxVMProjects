#include <iostream>
#include <pthread.h>  // for use of POSIX threads
#include <unistd.h>  // for use of sleep() function

using namespace std;

int bufferSize = 10;  // set size of shared buffer that the producer and consumer will insert and extract data from
int producedCount = 0;  // initialize an integer variable to count the number of items the producer has produced. set to 0 to start
int consumedCount = 0;  // initialize an integer variable to count the number of items the consumer has consumed. set to 0 to start
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // statically initialize a pthread mutex variable that will be shared by producer and consumer

// define the produce function that will be passed to create pthread as the routine for the thread to execute
void *produce(void *arg) {
    // begin infinite loop
    while(1) {
        pthread_mutex_lock(&mutex);  // lock mutex so that the producer can begin inserting data into buffer

        // if produced count is less than buffer size, there is still space in the buffer for producer to insert into
        if(producedCount < bufferSize) {
            producedCount++;  // increment produced count, representing the producer inserting one item into buffer
            cout << "Producer: \"I am producing " << producedCount << "\"" << endl;
            *((int*)arg) += 1;  // increment the argument passed in, which will represent the number of items produced by one producer 
            pthread_mutex_unlock(&mutex);  // unlock mutex so that consumer can access buffer
        }
        // if produced count is not less than buffer size, the buffer is full - producer has finished adding all items
        else {
            pthread_mutex_unlock(&mutex);  // unlock the mutex so that consumer can access buffer
            return NULL;  // break out of loop, function returns NULL
        }
    }
}

// define the consume function that will be passed to create pthread as the routine for the thread to execute
void *consume(void *arg) {
    // begin infinite loop
    while(1) {
        pthread_mutex_lock(&mutex);  // lock mutex so that the consumer can begin extracting from buffer

        // if consumed count is less than produced count, there are still items in buffer for consumer of extract
        if(consumedCount < producedCount) {
            consumedCount++;  // increment consumed count, representing consumer extracting one item from buffer
            cout << "Consumer: \"I am consuming " << consumedCount << "\"" << endl;
            *((int*)arg) += 1;  // increment the argument passed in, which will represent the number of items consumed by one consumer
            pthread_mutex_unlock(&mutex);  // unlock mutex
        }
        
        else {
            pthread_mutex_unlock(&mutex);  // unlock mutex

            // if consumed count is greater than or equal to buffer size, consumer has consumed all items from buffer
            if(consumedCount >= bufferSize) {
                return NULL;  // break out of loop, function returns NULL
            }
        }
    }
}

int main() {

    // initialize integer variables to hold number of producer and consumers
    int prodThreads, consThreads;
    
    cout << "\nEnter the number of producers: ";  // prompt user
    cin >> prodThreads;  // assign input to prodThreads

    cout << "\nEnter the number of consumers: ";  // prompt user
    cin >> consThreads;  // assign input to consThreads

    int producerArr[prodThreads], consumerArr[consThreads];  // initialize integer arrays, size specified by above user input
    pthread_t producerID[prodThreads], consumerID[consThreads];  // initialize pthread arrays, size specified by above user input
    pthread_setconcurrency(prodThreads + consThreads);  

    // iterate through loop for each producer thread
    for(int i = 0; i < prodThreads; i++) {
        producerArr[i] = 0;  // number produced starts at 0
        pthread_create(&producerID[i], NULL, produce, &producerArr[i]);  // create pthread
    }

    // iterate through loop for each consumer thread
    for(int i = 0; i < consThreads; i++) {
        consumerArr[i] = 0;
        pthread_create(&consumerID[i], NULL, consume, &consumerArr[i]);
    }

    for(int i = 0; i < prodThreads; i++) {
        pthread_join(producerID[i], NULL);
        cout << "\nProducer #" << i << " produced: " << producerArr[i] << " items" << endl;
        sleep(5);
    }

    cout << endl;

    for(int i = 0; i < consThreads; i++) {
        pthread_join(consumerID[i], NULL);
        cout << "\nConsumer #" << i << " consumed: " << consumerArr[i] << " items" << endl;
        sleep(5);
    }


    return 0;
}