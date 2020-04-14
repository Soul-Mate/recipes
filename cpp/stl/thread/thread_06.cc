#include <thread>
#include <iostream>

class bar
{
public:
    void foo(int x, int y)
    {
        x = x << y;
        std::cout << x << std::endl;
    }
};

int main()
{
    // thread with class member
    std::thread t(&bar::foo, bar(), 1, 16);
    t.join();
}