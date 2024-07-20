cmake_minimum_required(VERSION 3.14)
project(Fuse)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/Lib)

include_directories(${SOURCE_DIR})

add_library(Fuse STATIC)

file(GLOB INTERFACES ${SOURCE_DIR}/Interfaces/*.cpp ${SOURCE_DIR}/Interfaces/*.h)
file(GLOB COMPONENTS ${SOURCE_DIR}/Components/*.cpp ${SOURCE_DIR}/Components/*.h)

target_sources(Fuse PRIVATE
        # Universal sources
        Lib/Fuse.h
        Lib/Types.h
        Lib/Traits.h
        Lib/Converters.h
        Lib/Maths.h
        Lib/Size.h
        Lib/Offset.h
        Lib/Offset.cpp
        Lib/Color.h
        Lib/Color.cpp
        Lib/Stroke.h
        Lib/Font.h
        Lib/Input.h
        Lib/Rectangle.h
        Lib/Rectangle.cpp
        Lib/Polygon.h
        Lib/Platform/Platform.h
        # Interfaces
        ${INTERFACES}
        # Components
        ${COMPONENTS}
)

if (WIN32)
    add_definitions(-DPLATFORM_WINDOWS)
    target_sources(Fuse PRIVATE
            Lib/Platform/Win32PluginView.cpp
            Lib/Platform/Win32PluginView.h
            Lib/Backends/Direct2DBackend.cpp
            Lib/Backends/Direct2DBackend.h
    )
elseif (UNIX AND NOT APPLE)
    add_definitions(-DPLATFORM_LINUX)
    # Check for X11
    find_package(X11 QUIET)
    if (X11_FOUND)
        message(STATUS "X11 libraries found")
    else ()
        message(STATUS "X11 libraries not found")
    endif ()

    # Check for Wayland
    find_package(PkgConfig)
    pkg_check_modules(WAYLAND_CLIENT QUIET wayland-client)

    if (WAYLAND_CLIENT_FOUND)
        message(STATUS "Wayland libraries found")
    else ()
        message(STATUS "Wayland libraries not found")
    endif ()

    # Determine the active windowing system and set preprocessor defines
    if (DEFINED ENV{WAYLAND_DISPLAY})
        message(STATUS "Wayland is the active windowing system")
        add_definitions(-DUSE_WAYLAND)

        target_sources(Fuse PRIVATE
                Lib/Platform/WaylandPluginView.cpp
                Lib/Platform/WaylandPluginView.h
                Lib/Backends/CairoBackend.cpp
                Lib/Backends/CairoBackend.h
        )

        pkg_check_modules(WAYLAND_EGL REQUIRED wayland-egl)
        pkg_check_modules(WAYLAND_PROTO REQUIRED wayland-protocols)
        pkg_check_modules(EGL REQUIRED egl)
        target_link_libraries(Fuse PRIVATE wayland-client wayland-egl wayland-protocols egl)
    elseif (DEFINED ENV{DISPLAY})
        message(STATUS "X11 is the active windowing system")
        add_definitions(-DUSE_X11)

        target_sources(Fuse PRIVATE
                Lib/Platform/X11PluginView.cpp
                Lib/Platform/X11PluginView.h
                Lib/Backends/CairoBackend.cpp
                Lib/Backends/CairoBackend.h
        )
        target_link_libraries(Fuse PRIVATE X11)
    else ()
        message(STATUS "No active windowing system detected")
    endif ()

    # Link Cairo for all linux platforms
    pkg_check_modules(CAIROMM REQUIRED cairomm-1.16)
    include_directories(${CAIROMM_INCLUDE_DIRS})
    target_link_libraries(Fuse PRIVATE ${CAIROMM_LIBRARIES})
elseif (APPLE)
    add_definitions(-DPLATFORM_APPLE)
endif ()

if (MSVC)
    # Disable warning C4996
    target_compile_options(Fuse PRIVATE /wd4996)
endif ()

add_subdirectory(Examples)