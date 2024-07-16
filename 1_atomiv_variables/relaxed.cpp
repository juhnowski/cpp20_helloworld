#include <vector>
#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

atomic<int> count = {0};

void add() {
    for (int n=0; n< 1000; ++n) {
        count.fetch_add(1, memory_order_relaxed);
    }
}

int main() {
    vector<thread> v;
    
    for (int n=0; n<10; ++n) {  // первая точка синхронизации
        v.emplace_back(add);    // все операции выполняются попорядку
    }                           // add выполняется параллельно в каждом потоке

    for (auto& t:v) {
        t.join();               // вторая точка синхронизации, играет роль операции освобожднеия
    }

    cout << "Final counter value is " << count << endl;
}

