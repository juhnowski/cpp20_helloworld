// Прерываемый и непрерываемый потоки

#include <chrono>
#include <iostream>
#include <thread>

using namespace std;
using namespace literals;

int main(){

    cout << endl;

    jthread nonInterruptuble( [] {
        int counter{0};
        while (counter < 10){
            this_thread::sleep_for(0.2s);
            cerr << "nonInterruptuble:" << counter << endl;
            ++counter;
        }
    });

    jthread interruptuble( [](stop_token stoken) {
        int counter{0};
        while (counter < 10){
            this_thread::sleep_for(0.2s);
            if (stoken.stop_requested()) return;
            cerr << "interruptuble:" << counter << endl;
            ++counter;
        }
    });

    this_thread::sleep_for(1s);

    cerr << endl;

    cerr << "Main thread interrupts both jthreads" << endl;
    nonInterruptuble.request_stop();
    interruptuble.request_stop();

    cout << endl;
}