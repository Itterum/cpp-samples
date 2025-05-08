cmake_minimum_required(VERSION 3.31)
project(cpp_samples)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp)
add_executable(image_manager image_manager.cpp)

set(CMAKE_CXX_FLAGS_RELEASE "-Os -s -fno-exceptions -fno-rtti -static")
