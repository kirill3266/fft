cmake_minimum_required(VERSION 3.20)
project(Ann)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ann main.cpp fft.cpp BigInt.cpp)
