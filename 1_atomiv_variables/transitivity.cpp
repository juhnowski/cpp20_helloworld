#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

vector<int> mySharedWork;
atomic<bool> dataProduced(false);
atomic<bool> dataConsumed(false);

void dataProducer() {
    mySharedWork = {1,0,3};
    dataProduced.store(true, memory_order_release);     //--+
}                                                       //  |
                                                        //  |
void deliveryBoy() {                                    //  |
    while(!dataProduced.load(memory_order_acquire));    //<-+
    dataConsumed.store(true, memory_order_release);     //--+
}                                                       //  |
                                                        //  |
void dataConsumer() {                                   //  |
    while (!dataConsumed.load(memory_order_acquire));   //<-+
    mySharedWork[1] = 2;
}

int main() {
    cout << endl;

    thread t1(dataConsumer);
    thread t2(deliveryBoy);
    thread t3(dataProducer);

    t1.join();
    t2.join();
    t3.join();

    for (auto v: mySharedWork) {
        cout << v << " ";
    }

    cout << endl;
}