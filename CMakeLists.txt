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
        Lib/Platform/Platform.h
        # Interfaces
        ${INTERFACES}
        # Components
        ${COMPONENTS}
)

file(GLOB EXAMPLE_SOURCE
        Examples/CanvasHelloWorld.cpp
        Examples/CanvasHelloWorld.h
        Examples/CustomComponent.h
        Examples/CustomComponent.cpp
)

if (WIN32)
    target_sources(ArkVector PRIVATE
            Lib/Platform/Win32PluginView.cpp
            Lib/Platform/Win32PluginView.h
            Lib/Backends/Direct2DBackend.cpp
            Lib/Backends/Direct2DBackend.h
    )

    add_executable(HelloWorld.Win32 WIN32
            Examples/HWNDParent.h
            Examples/HelloWorld_Win32.cpp
            ${EXAMPLE_SOURCE}
    )
    target_link_libraries(HelloWorld.Win32 PRIVATE ArkVector)
elseif (UNIX AND NOT APPLE)
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

        target_sources(ArkVector PRIVATE
                Lib/Platform/WaylandPluginView.cpp
                Lib/Platform/WaylandPluginView.h
                Lib/Backends/CairoBackend.cpp
                Lib/Backends/CairoBackend.h
        )

        pkg_check_modules(WAYLAND_EGL REQUIRED wayland-egl)
        pkg_check_modules(EGL REQUIRED egl)
        target_link_libraries(ArkVector PRIVATE wayland-client wayland-egl egl)

        add_executable(HelloWorld.Wayland ${EXAMPLE_SOURCE} Examples/HelloWorld_Linux_Wayland.cpp
                Examples/WaylandParent.h)
        target_link_libraries(HelloWorld.Wayland PRIVATE ArkVector)
    elseif (DEFINED ENV{DISPLAY})
        message(STATUS "X11 is the active windowing system")
        add_definitions(-DUSE_X11)

        target_sources(ArkVector PRIVATE
                Lib/Platform/X11PluginView.cpp
                Lib/Platform/X11PluginView.h
                Lib/Backends/CairoBackend.cpp
                Lib/Backends/CairoBackend.h
        )
        target_link_libraries(ArkVector PRIVATE X11)

        add_executable(HelloWorld.X11 ${EXAMPLE_SOURCE} Examples/HelloWorld_Linux_X11.cpp
                Examples/X11Parent.h)
        target_link_libraries(HelloWorld.X11 PRIVATE ArkVector)
    else ()
        message(STATUS "No active windowing system detected")
    endif ()

    # Link Cairo for all linux platforms
    pkg_check_modules(CairoMM REQUIRED cairomm-1.16)
    target_link_libraries(ArkVector PRIVATE cairomm)
elseif (APPLE)
endif ()

if (MSVC)
    # Disable warning C4996
    target_compile_options(ArkVector PRIVATE /wd4996)
endif ()