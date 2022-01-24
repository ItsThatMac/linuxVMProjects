/*
Ethan Macalaguim and Kayla Zantello
CST-315: Operating Systems
Assignment 1: Producer and Consumer
January 23, 2022

Task: Implement functions for a producer and a consumer.
Both functions share a buffer, the producer inserts data in to the buffer,
and the consumer extracts data from the buffer. The goal is to create a 
program that ensures that the producer is always ahead of the consumer.

Solution: Use a mutex that each function will lock before completing
its task, then unlock once the task is complete, allowing for a smooth
back and forth transfer of data.
*/

#include <iostream>  
#include <pthread.h>  // for use of pthreads
#include <unistd.h>  // for use of sleep() function

using namespace std;

int bufferSize = 5;  // integer variable to specify the size of the buffer
int producedCount = 0;  // integer variable to keep track of how many pieces of data have been produced
int consumedCount = 0;  // integer variable to keep track of how many pieces of data have been consumed
bool pFinished = false;  // boolean variable to specify whether or not production has finished
bool cFinished = false;  // boolean variable to specify whether or not consumption has finished
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // initialize mutex that will be shared between producer and consumer

// produce function to be passed to create pthread, arg will be produced count
void *produce(void *arg) {
    // begin infinite loop
    while(1) {
        pthread_mutex_lock(&mutex);  // lock mutex so producer can access buffer and insert data without consumer interference
        cout << "\nP: locked mutex" << endl;  // display action to user

        // check to see if there is still space in the buffer
        if(producedCount < bufferSize) {
            *((int*)arg) += 1;  // if there is, produce an item by incrementing produced count
            cout << "P: produced " << producedCount << endl;  // display action to user
            pthread_mutex_unlock(&mutex);  // unlock mutex so consumer can access buffer
            cout << "P: unlocked mutex" << endl;  // display action to user
        }
        // if there is not space in the buffer
        else {
            pthread_mutex_unlock(&mutex);  // unlock mutex
            cout << "P: production complete, unlocked mutex" << endl;  // display status and action to user
            pFinished = true;  // production has finished, as all spots in buffer are full
            return NULL;  // break out of loop, terminating the process
        }
    }
}

// consume function to be passed to create pthread, arg will be consumed count
void *consume(void *arg) {
    // begin infinite loop
    while(1) {
        pthread_mutex_lock(&mutex);  // lock mutex so consumer can access buffer and extract data without producer interference 
        cout << "\nC: locked mutex" << endl;  // display action to user

        // check to see if there are still items to be consumed
        if(consumedCount < producedCount) {
            *((int*)arg) += 1;  // if there is, consume an item by incrementing consumed count
            cout << "C: consumed " << consumedCount << endl;  // display action to user
            pthread_mutex_unlock(&mutex);  // unlock mutex so producer can access buffer 
            cout << "C: unlocked mutex" << endl;  // display action to user
        }
        // if there are no items to be consumed
        else {
            // check to see if max number of items have been consumed
            if(consumedCount >= bufferSize) {
                pthread_mutex_unlock(&mutex);  // if they have, unlock mutex
                cout << "C: consumption complete, unlocked mutex" << endl;  // display status and action to user
                cFinished = true;  // consumption has finished
                return NULL;  // break out of the loop, terminating the process
            }

            // !!!! if program gets to this point, the producer is no longer ahead of the consumer
            pthread_mutex_unlock(&mutex);  // unlock mutex so producer can access
            cout << "C: nothing to consume, unlocked mutex" << endl;  // display failure status and action to user
        }
    }
}

// main function
int main() {

    pthread_t producerID, consumerID;  // pthread variables for producer and consumer

    pthread_create(&producerID, NULL, produce, &producedCount);  // create pthread to execute produce function
    
    pthread_create(&consumerID, NULL, consume, &consumedCount);  // create pthread to execute consume function

    // begin infinite loop
    while(1) {
        // check if production and consumption have both completed
        if(pFinished && cFinished) {
            // if they have, display final results of how many items were produced and consumed
            cout << "\nFINAL RESULTS:" << endl;
            sleep(2);

            cout << "The Producer produced: " << producedCount << " items" << endl;
            sleep(2);

            cout << "The Consumer consumed: " << consumedCount << " items" << endl;
            sleep(2);

            break;  // break out of loop once results have been displayed
        }
    }

    return 0;
}