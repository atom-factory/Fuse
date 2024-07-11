cmake_minimum_required(VERSION 3.14)
project(ArkVector)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libraries)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Binaries)

include_directories(
        Lib
)

add_library(ArkVector STATIC
        Lib/Types.h
        Lib/ArkVector.h
        Lib/ArkVector.cpp
        Lib/Platform.h
        Lib/Size.h
        Lib/Offset.cpp
        Lib/Offset.h
        Lib/Converters.h
        Lib/Maths.h
        Lib/Backends/Direct2DBackend.cpp
        Lib/Backends/Direct2DBackend.h
        Lib/Backends/OpenGLBackend.cpp
        Lib/Backends/OpenGLBackend.h
        Lib/Platform/AppWindow.h
        Lib/Platform/Win32AppWindow.cpp
        Lib/Platform/Win32AppWindow.h
)

add_executable(HelloWorld Examples/HelloWorld.cpp)
target_link_libraries(HelloWorld PRIVATE ArkVector)

if (MSVC)
    # Disable warning C4996
    target_compile_options(ArkVector PRIVATE /wd4996)
    target_compile_options(HelloWorld PRIVATE /wd4996)
endif ()