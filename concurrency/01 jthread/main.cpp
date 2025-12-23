// Created by Orlando Shamlou on 2025-12-21

// Using jthread means a joinable thread is joined when its destructor is called
// This code was written to better understand what that means
// Add breakpoint at start of ~jthread() and debug, compare what happens when a thread is joinable or not

#include <chrono>
#include <thread>

void eternal_loop()
{
    while (true)
    {}
}

void do_nothing()
{
    int a = 1;
}


int main()

{
    // (Un)comment lines to compare thread with jthread

    // std::thread t0(&do_nothing);
    std::jthread jt0(&do_nothing);
    jt0.join();

    // std::thread t1(&eternal_loop);
    // std::jthread jt1(&eternal_loop);

    // give time for thread to complete
    int wait_time = 1000;

    std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));

    return 0;
}