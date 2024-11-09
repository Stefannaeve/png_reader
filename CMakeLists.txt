cmake_minimum_required(VERSION 3.29)
project(PngReader C)

set(CMAKE_C_STANDARD 11)

add_executable(PngReader src/main.c
        include/main.h
        src/huffman.c
        include/huffman.h
        src/binaryTree.c
        include/binaryTree.h)
