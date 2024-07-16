#include <iostream>
#include <map>
#include <shared_mutex>
#include <string>
#include <thread>

using namespace std;

map<string, int> teleBook{
    {"Dijkstra", 1972},
    {"Scott", 1973},
    {"Ritchie", 1974}
};

shared_timed_mutex teleBookMutex;

void addToTeleBook(const string& na, int tele){
    lock_guard<shared_timed_mutex> writerLock(teleBookMutex);
    cout << endl << "STARTING UPDATE " << na << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    teleBook[na] = tele;
}

void printNumber(const string& na) {
    shared_lock<shared_timed_mutex> readerLock(teleBookMutex);
    cout << na << " : " << teleBook[na] << endl;
}

int main() {
    cout << endl;
    
    thread reader8([]{ printNumber("Bjarne"); });
    thread reader1([]{printNumber("Scott");});
    thread reader2([]{printNumber("Ritchie");});
    thread w1([]{addToTeleBook("Scott", 1968);});
    thread reader3([]{printNumber("Dijkstra");});
    thread reader4([]{printNumber("Scott");});
    thread w2([]{ addToTeleBook("Bjarne",1965); });
    thread reader5([]{ printNumber("Scott"); });
    thread reader6([]{ printNumber("Ritchie"); });
    thread reader7([]{ printNumber("Scott"); });
    
    reader8.join();
    reader1.join();
    reader2.join();
    reader3.join();
    reader4.join();
    reader5.join();
    reader6.join();
    reader7.join();

    w1.join();
    w2.join();

    cout << endl << "New book:" << endl;
    for (auto teleIt: teleBook) {
        cout << teleIt.first << " : " << teleIt.second << endl;
    }
    
    cout << endl;

}

/*
ПРОБЛЕМА:
- присутствует гонка данных
гонка данных – это ситуация, когда по меньшей
мере два потока имеют одновременный доступ к некоторой переменной
и хотя бы один из потоков производит её запись.

teleBook[na] - создает запись по ключу со значением 0, если ключ отсутствовал 
*/