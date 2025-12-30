// Created by Orlando Shamlou on 2025-12-29

// This code is taken from https://www.youtube.com/watch?v=XZDx41woDoI
// I have extended the code to better understand condition variables and to use notify_all()

// A working thread computes some results and appends them to a vector
// 2 reporting threads are blocked until the working thread has computed the result
// One reporter prints the result, another stringifies the vector size
// Only one reporter thread will work at a time
// The main thread prints the vector size when all threads are completed

// https://en.cppreference.com/w/cpp/thread/condition_variable.html
// When threads constantly check to see if they can acquire a lock, processor cycles are wasted
// A condition_variable blocks a thread or threads until another thread modifies a shared variable and notifies
// the condition_variable

#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>

std::mutex gLock;
std::condition_variable gConditionVariable;

void compute_and_append_values(int value, std::vector<int>& values, bool& notified)
{
    // Acquire the mutex
    std::unique_lock<std::mutex> lock(gLock);
    // Do our work, because we have the lock
    int result = value * 2 + 1;
    values.push_back(result);
    values.push_back(value + 1);
    values.push_back(0);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // Our work is done
    notified = true;
    std::cout << "Work complete." << std::endl;
    // Notify one of the waiting threads
    gConditionVariable.notify_all();
}

void print_vector(const std::vector<int>& values, const bool& notified)
{
    // Acquire the mutex
    std::unique_lock<std::mutex> lock(gLock);
    if (!notified)
    {
        // This unlocks the lock and blocks this thread
        gConditionVariable.wait(lock);
    }
    std::cout << "Values in vector: ";
    for (auto value : values)
    {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << value << ", ";
    }
    std::cout << std::endl;
}

void stringify_vector_size(const std::vector<int>& values, std::string& s, const bool& notified)
{
    // Acquire the mutex
    std::unique_lock<std::mutex> lock(gLock);
    if (!notified)
    {
        // This unlocks the lock and blocks this thread
        gConditionVariable.wait(lock);
    }
    std::this_thread::sleep_for(std::chrono::seconds(9));
    s = std::format("{}", values.size());
}

int main()
{
    std::vector<int> values{};

    // This is used to communicate between threads if work has been completed by the working thread
    bool notified = false;

    std::string vector_size;

    auto startTime = std::chrono::steady_clock::now();

    // Reporting threads must wait for working thread
    std::thread reporter1(print_vector, std::cref(values), std::cref(notified));
    std::thread reporter2(stringify_vector_size, std::cref(values), std::ref(vector_size), std::cref(notified));

    // Working thread must work first
    std::thread worker(compute_and_append_values, 42, std::ref(values), std::ref(notified));
    reporter1.join();
    reporter2.join();
    worker.join();
    std::cout << "Vector size is " << vector_size << std::endl;

    auto endTime = std::chrono::steady_clock::now();

    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count() << "s" << std::endl;

    // std::cout << "Time taken: " << timeTaken << std::endl;

    std::cout << "Program complete." << std::endl;
}