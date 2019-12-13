#include <iostream>
#include <iomanip>
#include <vector>
#include <future>
#include <random>
#include <cmath>
#include <chrono>

size_t sum(const std::vector<int> &nums, size_t low, size_t high)
{
    long long ret = 0;
    for (auto i = low; i < high && i < nums.size(); i++)
        ret += nums[i];

    return ret;
}

std::vector<int> get_nums(size_t size, int min = 1, int max = 20)
{
    std::cout << "make data... , size: " << size << std::endl;
    std::random_device rd;
    std::default_random_engine e(rd());
    std::uniform_int_distribution<> u(min, max);
    std::vector<int> v(size);
    for (size_t i = 0; i < size; i++)
        v[i] = u(e);

    std::cout << "end make data." << std::endl;
    return v;
}

auto use_async(const std::vector<int> &nums, size_t count)
{

    const size_t SINGLE = size_t(std::ceil(static_cast<long double>(nums.size()) / count));

    size_t ret = 0;
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::future<decltype(ret)>> futures;
    for (size_t i = 0; i < count; i++)
    {
        futures.emplace_back(std::async(sum, std::ref(nums), i * SINGLE, (i + 1) * SINGLE));
    }
    for (auto &f : futures)
        ret += f.get();

    auto end = std::chrono::high_resolution_clock::now();

    return std::make_pair(ret, end - start);
}

auto use_single(const std::vector<int> &nums)
{
    size_t ret = 0;
    auto start = std::chrono::high_resolution_clock::now();
    ret = sum(nums, 0, nums.size());
    auto end = std::chrono::high_resolution_clock::now();

    return std::make_pair(ret, end - start);
}

auto use_task(const std::vector<int> &nums, size_t count)
{
    const size_t SINGLE = size_t(std::ceil(static_cast<long double>(nums.size()) / count));

    size_t ret = 0;
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::future<decltype(ret)>> futures;
    for (size_t i = 0; i < count; i++)
    {
        std::packaged_task<decltype(ret)()> task(std::bind(sum, std::ref(nums), i * SINGLE, (i + 1) * SINGLE));
        futures.emplace_back(task.get_future());
        task();
    }
    for (auto &f : futures)
        ret += f.get();

    auto end = std::chrono::high_resolution_clock::now();

    return std::make_pair(ret, end - start);
}

auto use_task_thread(const std::vector<int> &nums, size_t count)
{
    const size_t SINGLE = size_t(std::ceil(static_cast<long double>(nums.size()) / count));

    size_t ret = 0;
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::future<decltype(ret)>> futures;
    std::vector<std::thread> threads;
    for (size_t i = 0; i < count; i++)
    {
        std::packaged_task<decltype(ret)()> task(std::bind(sum, std::ref(nums), i * SINGLE, (i + 1) * SINGLE));
        futures.emplace_back(task.get_future());
        threads.emplace_back(std::thread(std::move(task)));
    }

    for (auto &f : futures)
        ret += f.get();
    for (auto &t : threads)
        t.join();

    auto end = std::chrono::high_resolution_clock::now();

    return std::make_pair(ret, end - start);
}

int main(int, char **)
{
    const size_t SIZE = 1000000000; // vector size
    const size_t COUNT = 16;        // divided into COUNT parts
    const auto nums = get_nums(SIZE, 1, 50);

    using namespace std::chrono_literals;

    auto use_single_ret = use_single(nums);
    auto duration2 = std::chrono::duration<double, std::milli>(use_single_ret.second).count();
    std::cout << "single-thread result  : " << use_single_ret.first
              << "\tduration: " << duration2 << " ms"
              << std::endl;

    std::this_thread::sleep_for(5s);

    auto use_async_ret = use_async(nums, COUNT);
    auto duration1 = std::chrono::duration<double, std::milli>(use_async_ret.second).count();
    std::cout << "async-thread result   : " << use_async_ret.first
              << "\tduration: " << duration1 << " ms"
              << std::endl;

    std::this_thread::sleep_for(10s);

    auto use_task_ret = use_task(nums, COUNT);
    auto duration3 = std::chrono::duration<double, std::milli>(use_task_ret.second).count();
    std::cout << "single_task result    : " << use_task_ret.first
              << "\tduration: " << duration3 << " ms"
              << std::endl;

    std::this_thread::sleep_for(10s);

    auto use_task_thread_ret = use_task_thread(nums, COUNT);
    auto duration4 = std::chrono::duration<double, std::milli>(use_task_thread_ret.second).count();
    std::cout << "thread_task result    : " << use_task_thread_ret.first
              << "\tduration: " << duration4 << " ms"
              << std::endl;

    std::this_thread::sleep_for(10s);

    std::cout << std::setprecision(3)
              << "single / async       : " << double(duration2) / duration1 << std::endl
              << "single / task        : " << double(duration2) / duration3 << std::endl
              << "single / task_thread : " << double(duration2) / duration4 << std::endl;

    std::cout << "end." << std::endl;
    std::this_thread::sleep_for(10s);
}
