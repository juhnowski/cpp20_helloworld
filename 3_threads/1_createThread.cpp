// Создание потоков

#include <iostream>
#include <thread>

using namespace std;

void helloFunction() {
 cout << "Hello from function" << endl;
}

class HelloFuncObj {
    public:
        void operator()() const {
            cout << "Hello from func obj" << endl;
        }
};

int main() {
    cout << endl;
    
    thread t1(helloFunction);

    HelloFuncObj helloFuncObj;
    thread t2(helloFuncObj);

    thread t3([] {cout << "Hello from lambda"<< endl;});

    t1.join();
    t2.join();
    t3.join();

    cout << endl;
}