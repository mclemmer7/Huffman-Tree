cmake_minimum_required(VERSION 3.10)
project(huffman-mclemmer7)

set(CMAKE_CXX_STANDARD 14)

add_executable(huffman-mclemmer7 main.cpp frequencynode.cpp frequencynode.h tree.cpp tree.h encoding.cpp encoding.h)