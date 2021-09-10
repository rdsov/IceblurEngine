cmake_minimum_required(VERSION 3.20)
project(IceblurEngine)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(ICE_BUILD_DLL)

add_library(IceblurEngine SHARED Core/Core.h Core/Application.cpp Core/Application.h Core/CoreMinimal.h Core/HostEntry.h Core/IO/Log.cpp Core/IO/Log.h Platform/PlatformDetection.h Core/VTime.cpp Core/VTime.h Core/Window.h Event/EventSystem.h Event/EventSystem.cpp Event/EventTypes.h Event/IEvent.h Platform/Windows/Win64Window.cpp Platform/Windows/Win64Window.h Core/WindowManager.h Core/WindowManager.cpp Math/VMath.h Math/VMath.cpp Core/Error/ErrorList.cpp Core/Error/ErrorList.h)

add_custom_command(TARGET IceblurEngine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${LIBRARY_OUTPUT_PATH}/IceblurEngine.dll
        ${EXECUTABLE_OUTPUT_PATH}/IceblurEngine.dll)

target_precompile_headers(IceblurEngine
        PUBLIC
        <iostream>
        <string>
        <vector>
        <map>
        <filesystem>
        <fstream>
        <streambuf>
        <functional>
        )

target_link_libraries(IceblurEngine glad)
target_link_libraries(IceblurEngine glfw)
