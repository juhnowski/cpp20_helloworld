#include <iostream>
#include <thread>
#include <future>

using namespace std;
using namespace literals;


void function1(stop_token stopToken, const string& str){
    this_thread::sleep_for(1s);
    if (stopToken.stop_requested()) {
        cout << str << ": Stop requested" << endl;
    }
}

void function2(
    promise<void> prom,
    stop_token stopToken,
    const string& str
) {
    this_thread::sleep_for(1s);
    stop_callback callBack (stopToken, [&str]{
        cout << str << ": Stop requested" << endl;
    });
    prom.set_value();
}
int main() {
    cout << endl;
    stop_source stopSource;

    stop_token stopToken = stop_token(stopSource.get_token());

    thread thr1 = thread(function1, stopToken, "std::thread");

    jthread jthr = jthread(function1, stopToken, "std::jthread");

    auto fut1 = async([stopToken]{
        this_thread::sleep_for(1s);
        if (stopToken.stop_requested()) {
            cout << "std::async: Stop requested"<< endl;
        }
    });

    promise<void> prom;
    auto fut2 = prom.get_future();
    thread thr2(function2, move(prom), stopToken, "std::promise");

    stopSource.request_stop();
    if (stopToken.stop_requested()) {
        cout << "main: Stop requested" << endl;
    }

    thr1.join();
    thr2.join();
    jthr.join();
    cout << endl;
}

/*
Имея объект stopSource (объявлен в строке 29), можно создать объект stop-
Token (строка 31) и снимать с него копию при создании каждой единицы
выполнения: std::thread (строка 33), std::jthread (строка 35), std::async (стро-
ка 37) и std::promise (строка 45)
*/