#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <chrono>
#include <unistd.h>

void run()
{
    sleep(1);
    std::cout << "hello: thread[" << std::this_thread::get_id() << "]." << std::endl;
}

int main()
{
    auto threadNum = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    for (int i = 0; i < threadNum; i++)
    {
        threads.push_back(std::thread(run));
    }
}