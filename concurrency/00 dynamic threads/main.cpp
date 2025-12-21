// Created by Orlando Shamlou on 2025-12-20

// This code is to answer these questions
    // Q: 'can I create threads dynamically?'
        // A: yes
    // Q 'what happens if I create too many threads?'
        // A: poor performance

// Create a vector of threads and print from them in order.
// Threads do not print until all threads have been created.

// 2025-12-21
// I wrote this code before watching the next video in the series: https://www.youtube.com/watch?v=kfLE57ljoEE,
// which basically does the same thing.
// I've now added std::this_thread::get_id() demonstrate that each thread is unique.
// Renamed thread_id to thread_index to avoid ambiguity

#include <iostream>
#include <thread>
#include <vector>

void print_from_thread(int thread_index, std::atomic<int>* current_thread)
{
    while (thread_index != *current_thread)
    {
        // Wait until this is the current thread
    }
    // threads[0] is the second thread after main thread
    std::cout << "Printing from thread " << thread_index + 2 << "." << std::endl;
    std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;
}

int main()
{
    constexpr int total_threads = 100;

    // Prevent new threads from printing until this matches their id
    std::atomic<int> current_thread = -1;

    std::vector<std::unique_ptr<std::thread>> threads;
    // std::vector<std::thread> threads;

    std::cout << "Printing from total " << total_threads << " threads." << std::endl;

    std::cout << "Printing from main thread." << std::endl;
    std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;

    // Include main thread in thread count
    for (int i = 0; i < total_threads + -1; ++i)
    {
        threads.push_back(std::make_unique<std::thread>(&print_from_thread, i, &current_thread));
        // threads.push_back(std::thread(&print_from_thread, i, &current_thread));
    }

    // We care about the vector index, not the thread's id
    for (int i = 0; i < threads.size(); ++i)
    {
        current_thread = i;
        threads[i]->join();
        // threads[i].join();
    }

    std::cout << "Printing complete!" << std::endl;

    return 0;
}