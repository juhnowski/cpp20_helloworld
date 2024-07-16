// Несинхронизированный вывод в поток std::cout

#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

mutex coutMutex;

class Worker {
    public:
        Worker(string n):name(n){};
        void operator()(){
            for (int i=1; i<=3; ++i){
                this_thread::sleep_for(chrono::milliseconds(200));
                coutMutex.lock();
                cout << name << " : " << " work:" << i << " done!!!" << endl;
                coutMutex.unlock();
            }
        }
    private:
        string name;
};

int main() {
    cout << endl;
    cout << "Boss: Let's start working" << endl << endl;
    thread herb = thread(Worker("Herb"));
    thread andrei = thread(Worker("    Andrei"));
    thread scott = thread(Worker("    Scott"));
    thread bjarne = thread(Worker("        Bjarne"));
    thread bart = thread(Worker("        Bart"));
    thread jenne = thread(Worker("            Jenne"));

    herb.join();
    andrei.join();
    scott.join();
    bjarne.join();
    bart.join();
    jenne.join();

    cout << "Boss: let's go home" << endl;
    cout << endl;
}
/*
Это справедливо для всех глобальных потоков
ввода-вывода (std::cout, std::cin, std::cerr, std::clog): отправка данных в эти потоки
и получение данных из них потокобезопасны.
Говоря более формальным языком, одновременная запись в поток std::cout из не-
скольких потоков представляет собой состояние гонки, но не гонку данных. Это означает,
что результат вывода программы зависит от порядка выполнения потоков.
*/