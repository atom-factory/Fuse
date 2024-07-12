cmake_minimum_required(VERSION 3.14)
project(ArkVector)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libraries)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Binaries)

include_directories(
        Lib
)

add_library(ArkVector STATIC)
target_sources(ArkVector PRIVATE
        Lib/Types.h
        Lib/ArkVector.h
        Lib/ArkVector.cpp
        Lib/Platform/Platform.h
        Lib/Size.h
        Lib/Offset.cpp
        Lib/Offset.h
        Lib/Converters.h
        Lib/Maths.h
        Lib/Interfaces/PluginView.h
        Lib/Interfaces/Backend.h
        Lib/Interfaces/PluginView.cpp
)

if (WIN32)
    target_sources(ArkVector PRIVATE
            Lib/Platform/Win32PluginView.cpp
            Lib/Platform/Win32PluginView.h
            Lib/Backends/Direct2DBackend.cpp
            Lib/Backends/Direct2DBackend.h
    )

    add_executable(HWNDEmbeddedChild WIN32 Examples/HWNDEmbeddedChild.cpp)
    target_link_libraries(HWNDEmbeddedChild PRIVATE ArkVector)
elseif (UNIX AND NOT APPLE)
    target_sources(ArkVector PRIVATE
            Lib/Platform/X11PluginView.cpp
            Lib/Platform/X11PluginView.h
            Lib/Backends/X11Backend.cpp
            Lib/Backends/X11Backend.h
    )

    find_package(X11 REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(CAIROMM REQUIRED IMPORTED_TARGET cairomm-1.16)

    target_link_libraries(ArkVector PRIVATE X11 PkgConfig::CAIROMM)

    add_executable(X11EmbeddedChild Examples/X11EmbeddedChild.cpp)
    target_link_libraries(X11EmbeddedChild PRIVATE ArkVector)
elseif (APPLE)
    target_sources(ArkVector PRIVATE
            Lib/Backends/X11Backend.cpp
            Lib/Backends/X11Backend.h
    )

    add_executable(NSEmbeddedChild Examples/NSEmbeddedChild.cpp)
    target_link_libraries(NSEmbeddedChild PRIVATE ArkVector)
endif ()

if (MSVC)
    # Disable warning C4996
    target_compile_options(ArkVector PRIVATE /wd4996)
    target_compile_options(HWNDEmbeddedChild PRIVATE /wd4996)
endif ()