#include <iostream>
#include <vector>
#include <string>
#include <atomic>

using namespace std;

int main()
{
    /*
    в с++20 конструктор устанавливает в false
    */
    atomic_flag atomicFlag;

    cout << atomicFlag.test_and_set() << endl;
    cout << atomicFlag.test() << endl;

    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const string& word : msg)
    {
        cout << word << " ";
        
    }
    cout << endl;
}