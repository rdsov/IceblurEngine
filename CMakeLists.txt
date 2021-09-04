cmake_minimum_required(VERSION 3.20)
project(IceblurEngine)

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/Engine/Build/Win64/${CMAKE_BUILD_TYPE}/Editor")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/Engine/Build/Win64/${CMAKE_BUILD_TYPE}/Runtime")

include_directories("${PROJECT_SOURCE_DIR}/Engine/Source")

add_subdirectory("${PROJECT_SOURCE_DIR}/Engine/Source/Editor")
add_subdirectory("${PROJECT_SOURCE_DIR}/Engine/Source/Runtime")
