cmake_minimum_required(VERSION 3.20)
project(IceblurEngine)

set(CMAKE_CXX_STANDARD 17)

add_library(IceblurEngine SHARED Test.cpp Test.h)

add_custom_command(TARGET IceblurEngine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${LIBRARY_OUTPUT_PATH}/IceblurEngine.dll
        ${EXECUTABLE_OUTPUT_PATH}/IceblurEngine.dll)
