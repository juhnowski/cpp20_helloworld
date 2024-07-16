// Синхронизация с обработчиком сигнала
#include <atomic>
#include <cassert>
#include <csignal>
#include <iostream>
using namespace std;
atomic<bool> a{false};
atomic<bool> b{false};

extern "C" void handler(int) {
    if (a.load(memory_order_relaxed)) {
        atomic_signal_fence(memory_order_acquire); // барьер с семантикой захвата
        assert(b.load(memory_order_relaxed));
    }
}

int main() {
    // сигнал SIGTERM означает требование завершить программу
    signal(SIGTERM, handler); 
    b.store(true, memory_order_relaxed);
    atomic_signal_fence(memory_order_release); // барьер с семантикой освобождения
    a.store(true, memory_order_relaxed);
}

/* барьеры запрещают переупорядычивание операций:
- операции освобождения не могут перемещаться через барьер освобождения
- операции захвата - через барьер захвата
а следовательно 13 никогда не будет нарушено
*/