#include <iostream>
#include <thread>

using namespace std;

int main() {
    cout << endl;
    cout << boolalpha;
    
    thread thr{[] {
        cout << "Joinable thread" << endl;
    }};

    cout << "thr.joinable():" << thr.joinable() << endl;
    cout << endl;
}

/*
Завершается ошибкой так как поток не присоединен
*/