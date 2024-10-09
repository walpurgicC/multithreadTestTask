cmake_minimum_required(VERSION 3.12)
project(testTask LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_executable (testTask "testTask.cpp" "testTask.h" "timer.cpp" "settings.h" "ringBuffer.h" "ringBuffer.cpp" "threadSafeQueue.h" "threadSafeQueue.cpp")

