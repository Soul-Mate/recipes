#include <iostream>
#include <thread>
#include <chrono>

class background
{
public:
    void operator()() const
    {
        std::cout << "hello world" << std::endl;
    };

    ~background() {
        std::cout << this << std::endl;
    }

};

int main()
{
    background f;
    std::thread t(f);
    t.join();
    std::cout << "main done." << std::endl;
}