cmake_minimum_required(VERSION 3.20)
project(IceblurEngine)

set(CMAKE_CXX_STANDARD 17)

#Set corresponding output paths
set(RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Engine/Binaries/Win64/${CMAKE_BUILD_TYPE}/Editor")
set(LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Engine/Binaries/Win64/${CMAKE_BUILD_TYPE}/Runtime")

#Workaround for getting rid of the <Configuration> folder that Visual Studio adds
if (MSVC)
    # First for the generic no-config case (e.g. with mingw)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIRECTORY})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIRECTORY})
    # Second, for multi-config builds (e.g. msvc)
    foreach (OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${RUNTIME_OUTPUT_DIRECTORY})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${LIBRARY_OUTPUT_DIRECTORY})
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${LIBRARY_OUTPUT_DIRECTORY})
    endforeach (OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)
endif (MSVC)

#Disable unnecessary build targets
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories("${PROJECT_SOURCE_DIR}/Engine/Source")

#Add third party packages
add_subdirectory("${PROJECT_SOURCE_DIR}/Engine/Source/ThirdParty/GLFW")
add_subdirectory("${PROJECT_SOURCE_DIR}/Engine/Source/ThirdParty/GLAD")
add_subdirectory("${PROJECT_SOURCE_DIR}/Engine/Source/ThirdParty/GLM")

#Include engine and editor project
add_subdirectory("${PROJECT_SOURCE_DIR}/Engine/Source/Editor")
add_subdirectory("${PROJECT_SOURCE_DIR}/Engine/Source/Runtime")

#Set third party include paths
target_include_directories(IceblurEngine PUBLIC "${PROJECT_SOURCE_DIR}/Engine/Source/ThirdParty/GLFW/include")
target_include_directories(IceblurEngine PUBLIC "${PROJECT_SOURCE_DIR}/Engine/Source/ThirdParty/GLAD/include")
target_include_directories(IceblurEngine PUBLIC "${PROJECT_SOURCE_DIR}/Engine/Source/ThirdParty/GLM")

target_include_directories(IceblurEngine PUBLIC "${PROJECT_SOURCE_DIR}/Engine/Source/Runtime")
target_include_directories(IceblurEditor PUBLIC "${PROJECT_SOURCE_DIR}/Engine/Source/Editor")

#Set Visual Studio default startup project
if (MSVC)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT IceblurEditor)
endif (MSVC)
