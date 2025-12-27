// Created by Orlando Shamlou on 2025-12-27

// Uses a scoped lock to prevent deadlock
// This code follows the video at https://www.youtube.com/watch?v=Zp17-UDKM90

#include <iostream>
#include <thread>
#include <vector>

std::mutex global_lock;
int thread_count = 0;

void increment_thread_counter()
{
    std::scoped_lock<std::mutex> lock(global_lock);
    ++thread_count;
}

int main()
{
    std::vector<std::thread> threads;
    int number_of_threads = 100;
    for (int i = 0; i < number_of_threads; ++i)
    {
        threads.push_back(std::thread(&increment_thread_counter));
    }
    for (int i = 0; i < number_of_threads; ++i)
    {
        threads[i].join();
    }
    std::cout << "Thread count: " << thread_count << std::endl;
}