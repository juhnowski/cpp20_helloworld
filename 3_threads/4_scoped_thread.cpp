// scoped_thread Энтони Уильямса

#include <iostream>
#include <thread>
#include <utility>

using namespace std;

class scoped_thread{
std::thread t;
public:
explicit scoped_thread(std::thread t_): t(std::move(t_)){
if (!t.joinable()) throw std::logic_error("No thread");
}
~scoped_thread(){
t.join();
}
scoped_thread(scoped_thread&)= delete;
scoped_thread& operator=(scoped_thread const &)= delete;
};
