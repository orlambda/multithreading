// Created by Orlando Shamlou on 2025-12-23

// This builds on 00 dynamic threads, using a mutex to force threads to print one by one.
// This follows from watching https://www.youtube.com/watch?v=hXKtYRleQd8 but adapts my former code instead of
// using the video's code.
// Order of printing is not enforced, to demonstrate unpredictability..

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// Global variables for ease
std::mutex global_lock;

void print_from_thread(int thread_index)
{
    global_lock.lock();
        // threads[0] is the second thread after main thread
        std::cout << "Printing from thread " << thread_index + 2 << "." << std::endl;
        auto id = std::this_thread::get_id();
        std::cout << "Thread id: " << id << std::endl;
    global_lock.unlock();
}

int main()
{
    constexpr int total_threads = 100;

    std::vector<std::unique_ptr<std::thread>> threads;
    // std::vector<std::thread> threads;

    std::cout << "Printing from total " << total_threads << " threads." << std::endl;

    std::cout << "Printing from main thread." << std::endl;


    // Include main thread in thread count
    for (int i = 0; i < total_threads + -1; ++i)
    {
        threads.push_back(std::make_unique<std::thread>(&print_from_thread, i));
        // threads.push_back(std::thread(&print_from_thread, i));
    }

    // Allow time for all threads to run before joining
    int wait_time = 1000;
    std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));

    for (int i = 0; i < threads.size(); ++i)
    {
        threads[i]->join();
        // threads[i].join();
    }

    std::cout << "Printing complete!" << std::endl;
    std::cout << "Total number of threads: " << total_threads << std::endl;

    return 0;
}