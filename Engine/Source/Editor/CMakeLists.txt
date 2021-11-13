cmake_minimum_required(VERSION 3.20)
project(IceblurEditor)

set(CMAKE_CXX_STANDARD 17)

add_executable(IceblurEditor EditorApp.cpp EditorCamera.h EditorCamera.cpp)

#Change the working directory for Visual Studio
if (MSVC)
    set_property(TARGET IceblurEditor PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${RUNTIME_OUTPUT_DIRECTORY}")
endif (MSVC)

target_link_libraries(IceblurEditor IceblurEngine)
