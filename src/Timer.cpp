#include <iostream>

#include "Timer.hpp"
#include "TypeDefs.hpp"

void Timer::start()
{
    time_start = std::chrono::high_resolution_clock::now();

    std::cout << CYAN
              << "start :: "
              << RESET
              << this->_label
              << " \n";
}

void Timer::end()
{
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end - time_start;

    std::cout << CYAN
              << "end :: "
              << RESET
              << this->_label
              << " duration -> "
              << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count()
              << "ms \n";
}
