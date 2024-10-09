#include "timer.h"

void Timer::start()
{
    start_ = std::chrono::system_clock::now();
}

std::chrono::milliseconds Timer::elapsedTime()
{
    const auto end = std::chrono::system_clock::now();;

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start_);
}