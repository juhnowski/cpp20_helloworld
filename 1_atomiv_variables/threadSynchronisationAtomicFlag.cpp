#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

vector<int> myVec{};
atomic_flag atomicFlag;

void prepareWork() {
    myVec.insert(myVec.end(),{0,1,0,3});
    cout << "Sender: Data prepared." << '\n';
    atomicFlag.test_and_set();
    atomicFlag.notify_one();
}

void completeWork() {
    cout << "Waiter: waiting for data." << endl;
    atomicFlag.wait(false);
    myVec[2] = 2;
    cout << "Waiter: Complete the work." << endl;
    for (auto i:myVec) cout << i << " ";
    cout << endl;
}

int main() {
    cout << endl;
    
    thread t1(prepareWork);
    thread t2(completeWork);

    t1.join();
    t2.join();

    cout << endl;
}