cmake_minimum_required(VERSION 3.26)
project(ascii-generator)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
find_package(Stb REQUIRED)

add_executable(ascii_generator main.cpp
        lib/ImageProcessing.h
        lib/dithering.h
        lib/include.h
        lib/asciiGeneration.h)

target_link_libraries(ascii_generator PRIVATE CURL::libcurl)
target_include_directories(ascii_generator PRIVATE ${Stb_INCLUDE_DIR})
