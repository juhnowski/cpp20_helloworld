#include <chrono>
#include <mutex>
#include <thread>

using namespace std;

mutex mut;

void workOnResource() {
    mut.lock();
    this_thread::sleep_for(chrono::milliseconds(2000));
    mut.unlock();
}

int main() {
    thread t1(workOnResource);
    thread t2(workOnResource);

    t1.join();
    t2.join();
}