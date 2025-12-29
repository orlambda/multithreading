// Created by Orlando Shamlou on 2025-12-29

// A working thread computes a result
// A reporting thread is blocked until the working thread has computed the result

// This code is taken from https://www.youtube.com/watch?v=XZDx41woDoI
// I plan to add something to the code, e.g. another thread, to better understand condition variables

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

int main()
{
    int result = 0;

    // This is used to communicate between threads if work has been completed by the working thread
    bool notified = false;

    // Reporting thread must wait for working thread
    std::thread reporter([&]()
    {
        // Acquire a mutex
        std::unique_lock<std::mutex> lock(gLock);
        if (!notified)
        {
            // This unlocks the lock and blocks this thread
            gConditionVariable.wait(lock);
        }
        std::cout << "Reporter result is: " << result << std::endl;
    });
    // Working thread must work first
    std::thread worker([&]()
    {
        // Acquire a mutex
        std::unique_lock<std::mutex> lock(gLock);
        // Do our work, because we have the lock
        result = 42 * 2 + 1;
        // Our work is done
        notified = true;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Work complete." << std::endl;
        // Notify one of the waiting threads
        gConditionVariable.notify_one();
    });
    reporter.join();
    worker.join();

    std::cout << "Program complete." << std::endl;
}