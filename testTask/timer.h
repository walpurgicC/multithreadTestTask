#include <chrono>

class Timer
{
    std::chrono::time_point<std::chrono::system_clock> start_;
public:
    void start();
    std::chrono::milliseconds elapsedTime();
};