#ifndef TRIAL_TIMING_H
#define TRIAL_TIMING_H

#include <chrono>
#include <iostream>
#include <functional>

template <typename T>
T timing(const std::function<T()> &action)
{
    auto start = std::chrono::high_resolution_clock::now();
    T result = action();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> interval = end - start;
    std::cout << interval.count() << std::endl;
    return result;
}

#endif
