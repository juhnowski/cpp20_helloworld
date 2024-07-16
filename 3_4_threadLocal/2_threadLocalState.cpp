// Общее состояние для нескольких функций
#include <iostream>
#include <string>
#include <mutex>
#include <thread>

using namespace std;

mutex coutMutex;

thread_local string s("hello from ");

void first(){
    s+="first ";
}

void second(){
    s+="second ";
}

void third(){
    s+="third ";
}

void addThreadLocal(string const& s2){
    s += s2;

    first();
    second();
    third();

    //protect cout
    lock_guard<mutex> guard(coutMutex);
    cout << s << endl;
    cout << "&s: " << &s << endl;
    cout << endl;
}

int main() {
    cout << endl;
    thread t1(addThreadLocal, "t1: ");
    thread t2(addThreadLocal, "t2: ");
    thread t3(addThreadLocal, "t3: ");
    thread t4(addThreadLocal, "t4: ");

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}