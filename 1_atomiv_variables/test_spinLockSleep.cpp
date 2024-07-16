#include <atomic>
#include <chrono>
#include <thread>

using namespace std;

class Spinlock {
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

void workOnResource() {
    spin.lock();
    this_thread::sleep_for(chrono::milliseconds(2000));
    spin.unlock();
}

int main() {
    thread t1(workOnResource);
    thread t2(workOnResource);

    t1.join();
    t2.join();
}