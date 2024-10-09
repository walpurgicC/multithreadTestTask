#include <stdexcept>
#include <queue>
#include <condition_variable>
#include <mutex>

class OverflowError : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

template <typename T>
class ThreadSafeQueue
{
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable cond_;
    int size_;

public:
    ThreadSafeQueue(int size) : size_(size) {}

    void push(T&& data)
    {
        std::unique_lock<std::mutex> lock{ mutex_ };
        if (queue_.size() == size_)
        {
            throw OverflowError("Queue overflow!");
        }
        queue_.push(std::forward<T>(data));
        cond_.notify_one();
    }

    int waitAndPopWithSize(T& data)
    {
        std::unique_lock<std::mutex> lock{ mutex_ };
        cond_.wait(lock, [this] { return !queue_.empty(); });
        data = std::move(queue_.front());
        queue_.pop();
        return queue_.size();
    }

    void clear()
    {
        std::unique_lock<std::mutex> lock{ mutex_ };
        while (!queue_.empty())
        {
            queue_.pop();
        }
    }
};

//Class for synchronization of threads lifetime
class ThreadSynchronizer
{
    mutable std::mutex mutex_;
    std::condition_variable cond_;
    bool lock_ = true;
public:
    ThreadSynchronizer() {}

    void wait();

    void release();
};