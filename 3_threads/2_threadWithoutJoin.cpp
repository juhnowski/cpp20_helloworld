// Забытое ожидание завершения потока
#include <iostream>
#include <thread>

using namespace std;

int main() {
    thread t([]{cout<<this_thread::get_id<<endl;});
}

/*
Объект поток с завернутым в него объектом - joinable (присоединяемый),
если для него не вызвалась ни одна из функций-членов join detach. 

Деструктор потока в присоединяемом состоянии вызывает аварийное завершение
программы посредством std::terminate

Исправить - 3_threadWithJoin.cpp
*/