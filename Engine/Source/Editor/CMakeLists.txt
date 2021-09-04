cmake_minimum_required(VERSION 3.20)
project(IceblurEditor)

set(CMAKE_CXX_STANDARD 17)

add_executable(IceblurEditor Application.cpp)

target_link_libraries(IceblurEditor IceblurEngine)
