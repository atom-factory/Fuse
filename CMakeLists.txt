cmake_minimum_required(VERSION 3.14)
project(ArkVector)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libraries)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Binaries)

include_directories(
        Lib
)

add_library(ArkVector STATIC
        Lib/Backends/Backend.h
        Lib/Platform/AppWindow.cpp
        Lib/Platform/NSAppWindow.cpp
        Lib/Platform/NSAppWindow.h)
target_sources(ArkVector PRIVATE
        Lib/Types.h
        Lib/ArkVector.h
        Lib/ArkVector.cpp
        Lib/Platform.h
        Lib/Size.h
        Lib/Offset.cpp
        Lib/Offset.h
        Lib/Converters.h
        Lib/Maths.h
        Lib/Platform/AppWindow.h
)

if (WIN32)
    target_sources(ArkVector PRIVATE
            Lib/Platform/Win32AppWindow.cpp
            Lib/Platform/Win32AppWindow.h
            Lib/Backends/Direct2DBackend.cpp
            Lib/Backends/Direct2DBackend.h
    )
elseif (UNIX AND NOT APPLE)
    target_sources(ArkVector PRIVATE
            Lib/Platform/X11AppWindow.cpp
            Lib/Platform/X11AppWindow.h
            Lib/Backends/X11Backend.cpp
            Lib/Backends/X11Backend.h
    )

    find_package(X11 REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(CAIROMM REQUIRED IMPORTED_TARGET cairomm-1.16)

    target_link_libraries(ArkVector PRIVATE X11 PkgConfig::CAIROMM)
elseif (APPLE)
    target_sources(ArkVector PRIVATE
            Lib/Backends/X11Backend.cpp
            Lib/Backends/X11Backend.h
    )
endif ()

add_executable(HelloWorld Examples/HelloWorld.cpp)
target_link_libraries(HelloWorld PRIVATE ArkVector)

if (MSVC)
    # Disable warning C4996
    target_compile_options(ArkVector PRIVATE /wd4996)
    target_compile_options(HelloWorld PRIVATE /wd4996)
endif ()