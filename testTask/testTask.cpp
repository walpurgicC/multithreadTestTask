// testTask.cpp: определяет точку входа для приложения.
//

#include "testTask.h"

namespace
{
	void printToFile(char* data, int size, std::ostream& file_stream)
	{
		file_stream.write(data, size);
	}

    void produce(ThreadSafeQueue<std::pair<int, char*>>& queue, Settings const& settings, ThreadSynchronizer& synchronizer)
    {
        int remain_data_volume = settings.data_volume;
        Timer timer;

        const auto milliseconds_per_request = std::chrono::milliseconds(1000 / settings.rps);
        const auto chunk_size_bytes = settings.chunk_size_in_bytes;

        RingBuffer buffer(settings.buffer_size, chunk_size_bytes);

        for (;;)
        {
            if (remain_data_volume <= 0)
            {
                std::cout << "Producing is done" << std::endl;
                break;
            }
            --remain_data_volume;

            timer.start();
            char* data = buffer.write();
            try
            {
                queue.push(std::make_pair(chunk_size_bytes, data));
            }
            catch (const OverflowError& e)
            {
                std::cout << "Runtime error: " << e.what() << std::endl;
                queue.clear();
                queue.push(std::make_pair(-1, nullptr));
                synchronizer.wait();
                return;
            }

            const auto elapsedTime = timer.elapsedTime();
            if (elapsedTime < milliseconds_per_request)
            {
                std::this_thread::sleep_for(milliseconds_per_request - elapsedTime);
            }
        }
        queue.push(std::make_pair(-1, nullptr));
        synchronizer.wait();
    }

    void consume(ThreadSafeQueue<std::pair<int, char*>>& queue, Settings const& settings, ThreadSynchronizer& synchronizer)
    {
        int task_count = 0;
        std::chrono::milliseconds total_elapsed_time = std::chrono::milliseconds(0);
        Timer timer;
        std::ofstream output_file(settings.output_file, std::ios::app);
        for (;;)
        {

            std::pair<int, char*> result;
            const int size = queue.waitAndPopWithSize(result);
            ++task_count;
            if (result.first == -1)
            {
                std::cout << "Consuming is done" << std::endl;
                break;
            }
            timer.start();
            printToFile(result.second, result.first, output_file);
            total_elapsed_time += timer.elapsedTime();
            std::cout << "Average write speed is " << double(task_count) / total_elapsed_time.count() << " writes per millisecond;" << " Queue size is " << size << std::endl;
        }
        output_file.close();
        synchronizer.release();
    }

} //namespace

int main(int argc, char* argv[])
{
    try
    {
		if (argc < 4)
		{
			std::cout << "Not enough arguments!" << std::endl;
			return 0;
		}
		
        Settings settings{ std::stoi(std::string(argv[1])), std::stoi(std::string(argv[2])), 256, 1048576, std::string(argv[3]) };

        ThreadSafeQueue<std::pair<int, char*>> queue(256);
        ThreadSynchronizer synchronizer;

        std::thread producer(produce, std::ref(queue), std::ref(settings), std::ref(synchronizer));
        std::thread consumer(consume, std::ref(queue), std::ref(settings), std::ref(synchronizer));

        producer.join();
        consumer.join();
    }
    catch (const std::exception& e)
    {
        std::cout << "Runtime error: " << e.what() << std::endl;
        return 0;
    }
}
