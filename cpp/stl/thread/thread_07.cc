#include <iostream>
#include <thread>
#include <exception>

class threadScope
{
public:
    threadScope(std::thread t) : t_(std::move(t))
    {
        if (!t_.joinable())
        {
            throw std::logic_error("No thread");
        }
    };

    ~threadScope()
    {
        t_.join();
    };

    threadScope(const threadScope &rhs) = delete;

private:
    std::thread t_;
};

void run()
{
    std::cout << "hello world" << std::endl;
}

int main()
{

    std::thread t1([] {
        std::cout << "hello world" << std::endl;
    });

    t1.join();

    try
    {

        threadScope(std::move(t1)); // exception
    }
    catch (std::logic_error &e)
    {
        // non-exception
        threadScope(std::thread([] {
            std::cout << "hello world" << std::endl;
        }));

        std::cout << e.what() << std::endl;
    }
}