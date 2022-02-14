// monitor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <condition_variable> // std::condition_variale
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

std::mutex theMutex;
std::condition_variable conditionalVariable;

bool ready = false;
int theData = 0;
int count = 0;

int produceData() {
    int randomNumber = rand() % 100 + 1;
    std::cout << "///////////////////////////" << "\n" << "produce data: " << randomNumber << "\n" << "\n";
    return randomNumber;
}

void consumeData(int data) { std::cout << "///////////////////////////" << "\n" << "receive data: " << data << "\n" << "\n"; }

void consumer() {
    int data = 0;
    int count = 0;
    while (count < 10)
    {
        while (true) {
            std::unique_lock<std::mutex> ul(theMutex);
            // the monitor tht takes the input and determines whether or not to run the code.
            conditionalVariable.wait(ul, []() { return ready; });
            consumeData(rand() % theData + 1);
            ready = false;
            // the monitor then unlocks and allows the next process to continue
            ul.unlock();
            conditionalVariable.notify_one();
            // ignore the count, it does nothing.
            count++;
        }
    }
}

void producer() {
    int count = 0;
    while (count < 10)
    {
        while (true) {
            // a mutex lock is placed on the process based on what the monitor sees
            std::unique_lock<std::mutex> ul(theMutex);
            theData = produceData();
            ready = true;
            // it will unlock the lock to complete the process and notify the next process
            ul.unlock();
            conditionalVariable.notify_one();
            
            ul.lock();
            conditionalVariable.wait(ul, []() { return ready == false; });
            count++;
        }
    }
}

// Although I am using threads, it does not involve the pthread lock commands. 
// It is simply to create new threads to use my monitor lock on.
void consumerThread(int n) { consumer(); }

void producerThread(int n) { producer(); }

int main() {
    int times = 1;
    std::thread t1(consumerThread, times);
    std::thread t2(producerThread, times);
    t1.join();
    t2.join();
    return 0;
}



