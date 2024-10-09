#include "ringBuffer.h"

RingBuffer::~RingBuffer() { delete[] buff_; }

char* RingBuffer::write()
{
    const int block_start = chunk_size_ * write_;
    const int block_end = chunk_size_ * ++write_;
    for (int i = block_start; i < block_end; ++i)
    {
        buff_[i] = char(filler_);
    }

    if (write_ > size_ - 1)
    {
        write_ = 0;
        filler_ = 0;
    }
    ++filler_;

    return buff_ + block_start;
}