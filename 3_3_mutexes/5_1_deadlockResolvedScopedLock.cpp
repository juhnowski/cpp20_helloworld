#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>

using namespace std;

struct CriticalData {
    mutex mut;
};

void deadLock(CriticalData& a, CriticalData& b) {
    cout << "Thread: " << this_thread::get_id() << " first mutex" << endl;
    this_thread::sleep_for(chrono::milliseconds(1));
    cout << "Thread: " << this_thread::get_id() << " second mutex" << endl;

    scoped_lock(a.mut, b.mut);
}

int main() {
    cout << endl;

    CriticalData c1;
    CriticalData c2;

    thread t1([&]{deadLock(c1, c2);});
    thread t2([&]{deadLock(c2, c1);});

    t1.join();
    t2.join();

    cout << endl;
}