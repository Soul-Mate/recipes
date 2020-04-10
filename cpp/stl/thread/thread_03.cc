#include <iostream>
#include <thread>
#include <exception>
#include <unistd.h>

void background()
{
    sleep(2);
    std::cout << "hello world" << std::endl;
}


void exceptionFunc()
{
    throw std::logic_error("some exception");
}

int main(int argc, const char** argv) {

    std::thread t(background);
    try {
        exceptionFunc();
    } catch(std::logic_error &e) {
        std::cout << e.what() << std::endl;
        // 异常情况下的等待
        t.join();
        // 可以从此处rethrow, 这里因为是main，直接return
        return 0;
    }

    // 正常情况下的等待
    t.join(); 
    return 0;
}