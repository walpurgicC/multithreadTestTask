#include "threadSafeQueue.h"

void ThreadSynchronizer::wait()
{
    std::unique_lock<std::mutex> lock{ mutex_ };
    cond_.wait(lock, [this] { return !lock_; });
}

void ThreadSynchronizer::release()
{
    std::unique_lock<std::mutex> lock{ mutex_ };
    lock_ = false;
    cond_.notify_one();
}