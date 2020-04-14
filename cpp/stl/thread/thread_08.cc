#include <iostream>
#include <thread>
#include <vector>
#include <numeric> // std::accumulate

template <typename Iterator, typename T>
T accumulate_parallel(Iterator first, Iterator last, T init)
{
    auto length = std::distance(first, last);
    
    // std::thread::hardware_concurrency();
}

int main()
{
    std::vector<int> arr(20);
    for (std::size_t i = 0; i < arr.size(); i++)
    {
        arr.push_back(i + 1);
    }

    accumulate_parallel<std::vector<int>::iterator, int>(arr.begin(), arr.end(), 0);
}