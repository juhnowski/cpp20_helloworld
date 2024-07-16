#include <atomic>
#include <thread>
#include <iostream>

using namespace std;

class Spinlock{
    atomic_flag flag;
public:
    Spinlock(): flag(ATOMIC_FLAG_INIT) {}

    void lock() {
        while (flag.test_and_set(memory_order_acquire));
    }

    void unlock() {
        flag.clear(memory_order_release);
    }
};

Spinlock spin;

void workOnResource() {
    spin.lock();
    cout << "Shared resource" << endl;
    spin.unlock();
}

int main() {
    thread t1(workOnResource);
    thread t2(workOnResource);

    t1.join();
    t2.join();
}