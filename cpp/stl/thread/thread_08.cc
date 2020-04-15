#include <iostream>
#include <thread>
#include <vector>
#include <cstdio>
#include <numeric> // std::accumulate
#include <cmath>   // std::ceil
#include <chrono>

template <typename Iterator, typename T>
struct accumulateBlock
{
    void operator()(Iterator first, Iterator last, T &result)
    {
        result = std::accumulate(first, last, 0);
        // std::printf("thread-%d: accumulate: %llu\n", std::this_thread::get_id(), result);
    };
};

template <typename Iterator, typename T>
T accumulate_parallel(Iterator first, Iterator last, T init)
{
    auto length = std::distance(first, last);
    if (!length)
    {
        return init;
    }

    auto minAccumulateDistancePerThread = 1000;
    // length = 1000, accumulate per thread = 10000, actually threads = 1000 / 10000 = 0.1 and ceil after = 1
    auto accumulateThreadNum = static_cast<unsigned int>(std::ceil(length * 1.0 / minAccumulateDistancePerThread));

    // // std::cout << "minAccumulateDistancePerThread: " << minAccumulateDistancePerThread
    //           << ", accumulateThreadNum: " << accumulateThreadNum << std::endl;

    // threads by cpu core
    auto hardwareNum = std::thread::hardware_concurrency();

    // std::cout << "hardwareNum: " << hardwareNum << std::endl;

    // finally. actually allocate threads
    auto threadsNum = std::min(hardwareNum == 0 ? 2 : hardwareNum, accumulateThreadNum);
    // thread divide iterator distance
    auto iteratorAccumulateDistancePerTrhead = static_cast<unsigned int>(length / threadsNum);

    std::vector<std::thread> threads(threadsNum);
    std::vector<T> results(threadsNum + 1);

    // std::cout << "threadsNum: " << threadsNum << std::endl;

    Iterator iteratorStart, iteratorEnd;
    iteratorStart = first;
    for (decltype(threadsNum) i = 0; i < threadsNum; i++)
    {
        iteratorEnd = iteratorStart;
        // the end iterator advance iteratorAccumulateDistancePerTrhead length.
        std::advance(iteratorEnd, iteratorAccumulateDistancePerTrhead);

        threads[i] = std::thread(accumulateBlock<Iterator, T>(),
                                 iteratorStart, iteratorEnd, std::ref(results[i]));
        // update next thread start iterator
        iteratorStart = iteratorEnd;
    }

    for (auto &t : threads)
    {
        t.join();
    }

    // remaning calculation
    if (iteratorStart != last)
    {
        accumulateBlock<Iterator, T>()(iteratorStart, last, results[threadsNum]);
    }

    return std::accumulate(results.begin(), results.end(), init);
}

int main()
{

    int round = 100; // million

    std::vector<uint64_t> arr;
    for (int i = 0; i < 1000000; i++)
    {
        arr.push_back(i + 1);
    }

    std::printf("test:\nround: %d\nvector size: %d, accumulate [1-%d]\n", round, arr.size(), arr.size());

    std::printf("start native accumulate:\n\t");
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < round; i++)
    {
        std::accumulate(arr.begin(), arr.end(), 0);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::printf("execute: %lld ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count());

    std::printf("start parallel accumulate:\n\t");
    auto t3 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < round; i++)
    {
        accumulate_parallel(arr.begin(), arr.end(), 0);
    }
    auto t4 = std::chrono::high_resolution_clock::now();
    std::printf("execute: %lld ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count());
}