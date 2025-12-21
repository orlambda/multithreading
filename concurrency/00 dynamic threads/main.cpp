// Created by Orlando Shamlou on 2025-12-20

// This code is to answer these questions
    // Q: 'can I create threads dynamically?'
        // A: yes
    // Q 'what happens if I create too many threads?'
        // A: poor performance

// Create a vector of threads and print from them in order.
// Threads do not print until all threads have been created.

// 2025-12-21
/*
    I wrote the original code before watching the next video in the series: https://www.youtube.com/watch?v=kfLE57ljoEE,
    which basically does the same thing.
    I updated the code seeing the video use std::this_thread::get_id().
    Threads now print their id to demonstrate that each thread is unique.
    Renamed thread_id to thread_index to avoid ambiguity
    Added set of thread ids to check for duplicates
*/

#include <iostream>
#include <thread>
#include <unordered_set>
#include <vector>

// Global variables for ease
std::unordered_set<std::thread::id> ids;
std::atomic<bool> duplicate_id_found = false;

void print_from_thread(int thread_index, std::atomic<int>* current_thread)
{
    // Wait until this is the current thread
    while (thread_index != *current_thread)
        {}
    // threads[0] is the second thread after main thread
    std::cout << "Printing from thread " << thread_index + 2 << "." << std::endl;
    auto id = std::this_thread::get_id();
    std::cout << "Thread id: " << id << std::endl;
    if (ids.contains(id))
    {
        std::cout << "Duplicate id found." << std::endl;
        duplicate_id_found = true;
    }
    else
    {
        ids.insert(id);
    }
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
    ids.insert(std::this_thread::get_id());


    // Include main thread in thread count
    for (int i = 0; i < total_threads + -1; ++i)
    {
        threads.push_back(std::make_unique<std::thread>(&print_from_thread, i, &current_thread));
        // threads.push_back(std::thread(&print_from_thread, i, &current_thread));
    }

    // Tell each thread to print
    // We care about the vector index, not the thread's id
    for (int i = 0; i < threads.size(); ++i)
    {
        current_thread = i;
        threads[i]->join();
        // threads[i].join();
    }

    std::cout << "Printing complete!" << std::endl;
    std::cout << "Total number of threads: " << total_threads << std::endl;
    std::cout << "Total number of thread ids: " << ids.size() << std::endl;
    if (duplicate_id_found)
    {
        std::cout << "Duplicate thread id(s) were found." << std::endl;
    }
    else
    {
        std::cout << "No duplicate thread ids were found." << std::endl;
    }

    return 0;
}