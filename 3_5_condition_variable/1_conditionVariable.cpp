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
    //--------------------------------------------
    unique_lock<mutex> lck(mutex_);
    condVar.wait(lck, []{ return dataReady; });
    //эти две строки эквивалентны
    /*
    std::unique_lock<std::mutex> lck(mutex_); // поток захватывает мутекс
    while ( ![]{ return dataReady; }() ) {
        condVar.wait(lck);                  // освобождает мутекс и переводит поток в состояние ожидания
    }
    */
    doTheWork();
    cout << "Work done" << endl;
}

void setDataReady(){
    {
        lock_guard<mutex> lck(mutex_); // ждем пока стартанет waitingForWork()
        dataReady = true;
    }
    
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