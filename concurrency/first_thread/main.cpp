// Created by Orlando Shamlou on 2025-12-20
// Following https://www.youtube.com/watch?v=tGfG3u0CB7s
// Create a new thread and print from both threads in the correct order

#include <iostream>
#include <thread>

void print_from_thread(const std::string& s)
{
    std::cout << "Printing from new thread!" << std::endl;
    std::cout << s << std::endl;
}

int main()
{
    std::cout << std::thread::hardware_concurrency << " threads supported (this is just a hint)." << std::endl;
    std::thread new_thread(&print_from_thread, "Testing!");
    // Wait for the thread to finish its execution
    new_thread.join();
    // new_thread has now joined with the thread that called it
    std::cout << "Printing from main thread!" << std::endl;
    return 0;
}