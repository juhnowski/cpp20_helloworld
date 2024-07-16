// Несинхронизированный вывод в поток std::cout

#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

class Worker {
    public:
        Worker(string n):name(n){};
        void operator()(){
            for (int i=1; i<=3; ++i){
                this_thread::sleep_for(chrono::milliseconds(200));
                cout << name << " : " << " work:" << i << "done!!!" << endl;
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
Проблема: несинхронизированный вывод в cout
Решение: mutex
*/