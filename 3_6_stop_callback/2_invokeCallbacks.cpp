// можно регистрировать сколько угодно колбэков
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;
using namespace literals;

void func(stop_token stopToken) {
    this_thread::sleep_for(100ms);
    for (int i=0; i<=9; ++i){
        stop_callback cb(stopToken, [i] {cout << i;});
    }
    cout << endl;
}

int main() {
    cout << endl;
    jthread thr1 = jthread(func);
    jthread thr2 = jthread(func);

    thr1.request_stop();
    thr2.request_stop();
    
    cout << endl;
}