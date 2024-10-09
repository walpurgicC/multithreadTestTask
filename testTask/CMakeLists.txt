cmake_minimum_required(VERSION 3.12)
project(testTask LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_executable (testTask "main.cpp" "timer.h" "timer.cpp" "settings.h" "ringBuffer.h" "ringBuffer.cpp" "threadSafeQueue.h")

