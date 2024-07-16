// Атомарные операции с семантикой захвата и освобождения

#include <atomic>
#include <thread>
#include <iostream>
#include <string>

using namespace std;

atomic<string*> ptr;
int data1;
atomic<int> atoData;

void producer() {
    string* p = new string("C++11");                        // происходит ранее ptr.store
    data1 = 2011;                                           //        |
    atoData.store(2024, memory_order_relaxed);              //        v
    ptr.store(p, memory_order_release);                     // синхронизуется, происходит ранее чем стр.23
}                                                           //        |
                                                            //        |
void consumer() {                                           //        |
    string* p2;                                             //        |
    while(!(p2 = ptr.load(memory_order_acquire)));          //  <-----+  
    cout << "*p2:" << *p2 << endl;                          // происходят позже ptr.load
    cout << "data: " << data1 << endl;                      //        |
    cout << "atoData: " << atoData.load(memory_order_relaxed);//      v
}

int main() {
    cout << endl;

    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

    cout << endl;
}