// Передача в поток аргументов по ссылке

#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

class Sleeper{
    public:
        Sleeper(int& i_):i{i_}{};
        void operator() (int k){
            for (unsigned int j=0; j<=5; ++j){
                this_thread::sleep_for(chrono::milliseconds(100));
                i+=k;
            }
        }
    private:
        int& i;
};

int main() {
    cout << endl;
    int valSleeper = 1000;
    thread t(Sleeper(valSleeper), 5);
    t.detach();
    cout << "valSleeper=" << valSleeper << endl;

    cout << endl;
}

/* Проблемы:
    1) значение переменной valSleeper в конце оказывается равным 1000
    2) идентификатор дочернего потока на печать не выводится.

Дефекты:
1) потоки имеют ничем не ограниченный доступ к valSleeper
2) Время жизни главного потока завершается раньше, чем дочерний по-
ток успевает выполнить все свои вычисления и вывести свой иденти-
фикатор в поток2 std::cout

Следствие:
переводят программу в состояние гонки
состояние гонок выступает причиной гонки данных

Решение:
1) присоеденить поток
2) защитить переменную valSleeper мьютексом или сделать её атомарной.
*/