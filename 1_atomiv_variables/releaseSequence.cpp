#include <atomic>
#include <thread>
#include <iostream>
#include <mutex>

using namespace std;
using namespace chrono_literals;

atomic<int> atom{0};
int somethingShared{0};

void writeShared() {
    somethingShared = 2011;
    atom.store(2, memory_order_release);
}

void readShared() {
    while (!(atom.fetch_sub(1, memory_order_acquire) > 0)){
        this_thread::sleep_for(100ms);
       
    };
    
    cout << "somethingShared: " << somethingShared << endl;
    
}

int main() {
    cout << endl;

    thread t1(writeShared);
    thread t2(readShared);
    thread t3(readShared);

    t1.join();
    t2.join();
    t3.join();

    cout << "atom: " << atom << endl;

    cout << endl;
}