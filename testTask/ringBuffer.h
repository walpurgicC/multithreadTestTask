class RingBuffer
{
    int size_;
    int chunk_size_;
    char* buff_;
    int write_ = 0;
    int filler_ = 0;
public:
    RingBuffer(int size, int chunk_size) : size_(size), chunk_size_(chunk_size), buff_(new char[size_ * chunk_size_]) {};
    ~RingBuffer();
    char* write();
};