#include <iostream>
#include <thread>
#include <exception>
#include <unistd.h>

class threadGuard
{

public:
    explicit threadGuard(std::thread &t) : t_(t){};

    threadGuard(threadGuard const &) = delete;

    threadGuard &operator=(threadGuard const &) = delete;

    ~threadGuard()
    {
        std::cout << "~threadGuard" << std::endl;
        if (t_.joinable())
        {
            t_.join();
        }
    };

private:
    std::thread &t_;
};

void background()
{
    sleep(2);
    std::cout << "hello world" << std::endl;
}

void exceptionFunc()
{
    throw std::logic_error("some exception");
}

void func()
{
}

int main(int argc, const char **argv)
{
    std::thread t(background);
    // RAII
    // 一旦thread guard对象创建，即使发生了异常，
    // 中断了正常的流程，线程依然会join
    threadGuard tg(t);
    try
    {
        // 这里触发异常
        exceptionFunc();
    }
    catch (...)
    {
    }

    return 0;
}