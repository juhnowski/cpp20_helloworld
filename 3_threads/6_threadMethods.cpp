//Функции-члены класса std::thread

#include <iostream>
#include <thread>

using namespace std;

int main() {
    cout << boolalpha << endl;
    cout << "hardware_concurrency="<< thread::hardware_concurrency << endl;

    thread t1([]{cout << "t1 with id=" << this_thread::get_id << endl;});
    thread t2([]{cout << "t2 with id=" << this_thread::get_id << endl;});

    cout << endl;

    swap(t1,t2);

    cout << "from main t1 id=" << t1.get_id() << endl;
    cout << "from main t2 id=" << t2.get_id() << endl;

    cout << endl;

    cout << "main id=" << this_thread::get_id() << endl;

    cout << endl;

    cout << "t1.joinable()" << t1.joinable() << endl; 

    t1.join();
    t2.join();

    cout << endl;

    cout << "t1.joinable()" << t1.joinable() << endl; 

    cout << endl;

}