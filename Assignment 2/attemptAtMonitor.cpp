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

int produceData() {
    int randomNumber = rand() % 1000;
    std::cout << "produce data: " << randomNumber << "\n";
    return randomNumber;
}

void consumeData(int data) { std::cout << "receive data: " << data << "\n"; }

void consumer() {
    int data = 0;
    while (true) {
        std::unique_lock<std::mutex> ul(theMutex);
        conditionalVariable.wait(ul, []() { return ready; });
        consumeData(theData);
        ready = false;
        ul.unlock();
        conditionalVariable.notify_one();
    }
}

void producer() {
    while (true) {
        std::unique_lock<std::mutex> ul(theMutex);
        theData = produceData();
        ready = true;
        ul.unlock();
        conditionalVariable.notify_one();
        ul.lock();
        conditionalVariable.wait(ul, []() { return ready == false; });
    }
}

void consumerThread(int n) { consumer(); }

void producerThread(int n) { producer(); }

int main() {
    int times = 100;
    std::thread t1(consumerThread, times);
    std::thread t2(producerThread, times);
    t1.join();
    t2.join();
    return 0;
}
