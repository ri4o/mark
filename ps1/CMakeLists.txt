cmake_minimum_required(VERSION 3.27)
project(ps1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ps1
        bmp.c
        bmp.h
        playfair.c
        playfair.h)
