#include <iostream>
#include <thread>

using namespace std;

int main() {
    cout << endl;
    cout << boolalpha;
    
    jthread thr{[] {
        cout << "Joinable thread" << endl;
    }};

    cout << "thr.joinable():" << thr.joinable() << endl;
    cout << endl;
}