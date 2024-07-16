#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

vector<int> mySharedWork;
atomic<bool> dataReady(false);

void waitingForWork() {
    cout << "Waiting" << endl;

    while (!dataReady.load()) {
        this_thread::sleep_for(chrono::milliseconds(5));
    }

    mySharedWork[1] = 2;

    cout << "Work done" << endl;
}

void setDataReady() {
    mySharedWork = {1,0,3};
    dataReady = true;
    cout << "Data prepared" << endl;
}

int main() {
    cout << endl;

    thread t1(waitingForWork);
    thread t2(setDataReady);

    t1.join();
    t2.join();

    for (auto v: mySharedWork) {
        cout << v << " ";
    }

    cout << endl;
}