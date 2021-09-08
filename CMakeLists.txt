cmake_minimum_required(VERSION 3.20)
project(IceblurEngine)

set(CMAKE_CXX_STANDARD 17)

#Set corresponding output paths
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/Engine/Binaries/Win64/${CMAKE_BUILD_TYPE}/Editor")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/Engine/Binaries/Win64/${CMAKE_BUILD_TYPE}/Runtime")

#Disable unnecessary build targets
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories("${PROJECT_SOURCE_DIR}/Engine/Source")

#Add third party packages
add_subdirectory("${PROJECT_SOURCE_DIR}/Engine/Source/ThirdParty/GLFW")
add_subdirectory("${PROJECT_SOURCE_DIR}/Engine/Source/ThirdParty/GLAD")

#Include engine and editor project
add_subdirectory("${PROJECT_SOURCE_DIR}/Engine/Source/Editor")
add_subdirectory("${PROJECT_SOURCE_DIR}/Engine/Source/Runtime")

#Set third party include paths
target_include_directories(IceblurEngine PUBLIC "${PROJECT_SOURCE_DIR}/Engine/Source/ThirdParty/GLFW/include")
target_include_directories(IceblurEngine PUBLIC "${PROJECT_SOURCE_DIR}/Engine/Source/ThirdParty/GLAD/include")

target_include_directories(IceblurEngine PUBLIC "${PROJECT_SOURCE_DIR}/Engine/Source/Runtime")
target_include_directories(IceblurEditor PUBLIC "${PROJECT_SOURCE_DIR}/Engine/Source/Editor")
