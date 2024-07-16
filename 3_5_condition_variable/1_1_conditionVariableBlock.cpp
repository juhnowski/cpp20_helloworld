// conditionVariable.cpp

#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

using namespace std;
mutex mutex_;
condition_variable condVar;

bool dataReady{false};

void doTheWork() {
    cout << "Processing shared data" << endl;
}

void waitingForWork() {
    cout << "Worker: Waiting for work" << endl;
    unique_lock<mutex> lck(mutex_);
    condVar.wait(lck);
    doTheWork();
    cout << "Work done" << endl;
}

void setDataReady(){
    cout << "Sender: Data is ready." << endl;
    condVar.notify_one();
}

int main() {
    cout << endl;
    thread t1(waitingForWork);
    thread t2(setDataReady);

    t1.join();
    t2.join();

    cout << endl;
}

/*
При первом запуске программа отработала нормально. Однако на втором
запуске она зависла, так как отсылка оповещения одним потоком (строка 22)
произошла раньше, чем второй поток вошёл в режим ожидания (строка 15)
*/