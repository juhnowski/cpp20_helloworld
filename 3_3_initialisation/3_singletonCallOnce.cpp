#include <iostream>
#include <mutex>

using namespace std;

class MySingleton{
    private:
        static once_flag initInstanceFlag;
        static MySingleton* instance;
        MySingleton() = default;
        ~MySingleton() = default;
        
        static void initSingleton() {
            instance = new MySingleton();
        }
    public:
        MySingleton(const MySingleton&) = delete;
        MySingleton& operator = (const MySingleton&) = delete;

        static MySingleton* getInstance() {
            call_once(initInstanceFlag, MySingleton::initSingleton);
            return instance;
        }
};

MySingleton* MySingleton::instance = nullptr;
once_flag MySingleton::initInstanceFlag;

int main() {
        cout << endl;
        cout << "MySingleton::getInstance()" << MySingleton::getInstance() << endl;
        cout << "MySingleton::getInstance()" << MySingleton::getInstance() << endl;
        cout << endl;
}