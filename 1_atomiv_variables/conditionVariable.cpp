#include <condition_variable>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

vector<int> mySharedWork;
mutex mutex_;
condition_variable condVar;

bool dataReady{false};

void waitingForWork() {
    cout << "Waiting" << endl;
    unique_lock<mutex> lck(mutex_);
    condVar.wait(lck, []{return dataReady;});
    mySharedWork[1] = 2;
}

void setDataReady() {
    mySharedWork = {1,0,3};
    {
        lock_guard<mutex> lck(mutex_);
        dataReady = true;
    }
    cout << "Data prepared" << endl;
    condVar.notify_one();
}

int main() {
    cout << endl;
    
    thread t1(waitingForWork);
    thread t2(setDataReady);

    t1.join();
    t2.join();

    for (auto v:mySharedWork) {
        cout << v << " ";
    }

    cout << endl;
}