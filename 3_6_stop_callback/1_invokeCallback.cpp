#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;
using namespace std::literals;

auto func = [](stop_token stoken) {
    atomic<int> counter{0};
    auto thread_id = this_thread::get_id();
    stop_callback callBack(stoken, [&counter, thread_id] {
        cout << "id=" << thread_id << " ; counter="<< counter << endl;
    });
    while (counter < 10)
    {
        this_thread::sleep_for(0.2s);
        ++counter;
    }
    
};

int main() {
    cout << endl;
    vector<jthread> vecThreads(10);
    for (auto& thr: vecThreads) thr = jthread(func);

    this_thread::sleep_for(1s);
    for(auto& thr:vecThreads) thr.request_stop();

    cout << endl;
}


