// Порядок захвата и освобождения с использованием барьеров

#include <atomic>
#include <thread>
#include <iostream>
#include <string>

using namespace std;

atomic<string*> ptr;
int data1;
atomic<int> atoData;

void producer() {
    string* p = new string("C++11");
    data1 = 2011;
    atoData.store(2014, memory_order_relaxed); // ------------------------------------------------------------------+
    atomic_thread_fence(memory_order_release); // барьер с семантикой освобождения ---------------------+           |
    ptr.store(p, memory_order_relaxed);        // меняем семантику с освобождения на ослабленную        |           |
}   //                                                                                                  |   синхронизируется
    //                                                                                           синхронизируется   |
void consumer() { //                                                                                    |           |
    string* p2;   //                                                                                    |           |
    while(!(p2 = ptr.load(memory_order_relaxed))); //меняем семантику захвата на ослабленную <----------)-----------+
    atomic_thread_fence(memory_order_acquire); // барьер с семантикой захвата   <-----------------------+
    cout << "*p2:" << *p2 << endl;             //                                                происходят позже               
    cout << "data: " << data1 << endl;         //                                                       |                       
    cout << "atoData: " << atoData.load(memory_order_relaxed); //                                       v     
}

int main() {
    cout << endl;

    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

    cout << endl;
}

/* ИТОГО:
операции с ослабленной семантикой и неатомарные операции,
происходящие ранее барьера освобождения,
видны после барьера захвата
*/