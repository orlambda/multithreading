// Created by Orlando Shamlou on 2026-01-01

// This code is taken from https://www.youtube.com/watch?v=kECVa-SEZLY
// I will be extending the program to understand try_lock better

#include <iostream>
#include <mutex>
#include <thread>

std::mutex gLock;

void job1()
{
    gLock.lock();
        std::cout << "Job 1 is executed" << std::endl;
    gLock.unlock();
}

void job2()
{
    if (gLock.try_lock())
    {
        std::cout << "Job 2 is executed" << std::endl;
        gLock.unlock();
    }
    else
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(20ms);
        if (gLock.try_lock())
        {
            std::cout << "Job 2 is executed on 2nd attempt" << std::endl;
            gLock.unlock();
        }
    }
}

int main()
{
    std::thread thread1(&job1);
    std::thread thread2(&job2);

    thread1.join();
    thread2.join();
    return 0;
}