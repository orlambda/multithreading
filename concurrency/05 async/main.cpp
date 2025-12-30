// Created by Orlando Shamlou on 2025-12-30

// Learning about async and future

// Async lets you compute a result asynchronously (potentially in a separate thread), and continue in until get(),
// then wait for the result

// This program is based on code from https://www.youtube.com/watch?v=4twJD5ezkag

// I've added fast and slow versions of square() and timers to show how the slow function works in the background
// Slow function takes 6 seconds
// Quick function takes 1 second and is called 5 times

#include <iostream>
#include <future>

int slow_square(int x)
{
    std::this_thread::sleep_for(std::chrono::seconds(6));
    return x*x;
}

int quick_square(int x)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return x*x;
}

int main()
{
    auto startTime = std::chrono::steady_clock::now();

    // Start computing the slow function
    std::future<int> asyncFunction = std::async(&slow_square, 12);

    // Compute the quick functions
    for (int i = 0; i<5; ++i)
    {
        std::cout << quick_square(i) << std::endl;
    }

    // Time waiting for result from when quick functions are complete
    auto waitingStartTime = std::chrono::steady_clock::now();

    // We are blocked at get() until our result has computed
    int result = asyncFunction.get();

    auto endTime = std::chrono::steady_clock::now();

    std::cout << "Work complete." << std::endl;

    std::cout << "Result of slow function is: " << result << std::endl;

    std::cout << "Time spent waiting for async: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - waitingStartTime).count() << "ms" << std::endl;

    std::cout << "Time taken for all work: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms" << std::endl;

    return 0;
}