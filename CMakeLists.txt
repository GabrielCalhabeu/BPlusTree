cmake_minimum_required(VERSION 3.19)
project(BTrees C)

set(CMAKE_C_STANDARD 99)

include_directories(headers src)
add_executable(untitled src/main.c src/fileManager.c headers/fileManager.h
       headers/myB+.h src/myB+.c )