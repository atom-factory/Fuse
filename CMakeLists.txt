cmake_minimum_required(VERSION 3.14)
project(ArkVector)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/Lib)

include_directories(${SOURCE_DIR})

add_library(ArkVector STATIC)

file(GLOB INTERFACES ${SOURCE_DIR}/Interfaces/*.cpp ${SOURCE_DIR}/Interfaces/*.h)
file(GLOB COMPONENTS ${SOURCE_DIR}/Components/*.cpp ${SOURCE_DIR}/Components/*.h)

target_sources(ArkVector PRIVATE
        # Universal sources
        Lib/ArkVector.h
        Lib/Types.h
        Lib/Traits.h
        Lib/Converters.h
        Lib/Maths.h
        Lib/Size.h
        Lib/Offset.h
        Lib/Offset.cpp
        Lib/Color.h
        Lib/Color.cpp
        # Interfaces
        ${INTERFACES}
        # Components
        ${COMPONENTS}
)

if (WIN32)
    target_sources(ArkVector PRIVATE
            Lib/Platform/Win32PluginView.cpp
            Lib/Platform/Win32PluginView.h
            Lib/Backends/Direct2DBackend.cpp
            Lib/Backends/Direct2DBackend.h
    )

    add_executable(HelloWorld WIN32
            Examples/HWNDParent.h
            Examples/HelloWorld_Win32.cpp
            Examples/CanvasHelloWorld.cpp
            Examples/CanvasHelloWorld.h
            Examples/CustomComponent.h
            Examples/CustomComponent.cpp
    )
    target_link_libraries(HelloWorld PRIVATE ArkVector)
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

    add_executable(X11EmbeddedChild Examples/HelloWorld_Linux.cpp)
    target_link_libraries(X11EmbeddedChild PRIVATE ArkVector)
elseif (APPLE)
    #    target_sources(ArkVector PRIVATE
    #            Lib/Backends/X11Backend.cpp
    #            Lib/Backends/X11Backend.h
    #    )

    add_executable(NSEmbeddedChild Examples/HelloWorld_Apple.cpp)
    target_link_libraries(NSEmbeddedChild PRIVATE ArkVector)
endif ()

if (MSVC)
    # Disable warning C4996
    target_compile_options(ArkVector PRIVATE /wd4996)
endif ()