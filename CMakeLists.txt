cmake_minimum_required(VERSION 3.26)
project(ascii-generator)

set(CMAKE_CXX_STANDARD 17)

# Find required packages
find_package(CURL REQUIRED)
find_package(Stb REQUIRED)

# Define the executable and its source files
add_executable(ImagePull cpp/ImagePull.cpp)
add_executable(EditContrast cpp/EditContrast.cpp)
add_executable(GrayScale cpp/GrayScale.cpp)
add_executable(AsciiGeneration cpp/AsciiGeneration.cpp)
add_executable(DitherImage cpp/DitherImage.cpp
        lib/dithering.h)

# Link the executable with required libraries
target_link_libraries(ImagePull PRIVATE CURL::libcurl)
target_include_directories(ImagePull PRIVATE ${Stb_INCLUDE_DIR})

target_include_directories(EditContrast PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(GrayScale PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(DitherImage PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(AsciiGeneration PRIVATE ${Stb_INCLUDE_DIR})
