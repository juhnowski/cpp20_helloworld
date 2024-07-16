#include <atomic>
#include <thread>
#include <iostream>

using namespace std;

class Spinlock
{
    atomic_flag flag;

public:
    void lock() {
        while (flag.test_and_set());
    }        

    void unlock() {
        flag.clear();
    }
};

Spinlock spin;
int i = 0;

void workOnResource() {
    spin.lock();
    // shared res
    i++;
    spin.unlock();
}

int main() {
    thread t1(workOnResource);
    thread t2(workOnResource);
    
    t1.join();
    t2.join();

    cout << "i=" << i << endl;
}
