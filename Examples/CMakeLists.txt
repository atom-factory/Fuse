cmake_minimum_required(VERSION 3.14)
project(Fuse)

set(CMAKE_CXX_STANDARD 23)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ../Lib
)

file(GLOB SHARED_SOURCE
        Shared/CanvasHelloWorld.cpp
        Shared/CanvasHelloWorld.h
        Shared/BackgroundCutout.h
        Shared/BackgroundCutout.cpp
)

if (WIN32)
    add_executable(HelloWorld.Win32 WIN32
            Windows/HWNDParent.h
            Windows/HelloWorld_Win32.cpp
            ${SHARED_SOURCE}
            Res/app.rc
            Res/resource.h
    )
    target_link_libraries(HelloWorld.Win32 PRIVATE Fuse)
elseif (UNIX AND NOT APPLE)
    if (DEFINED ENV{WAYLAND_DISPLAY})
        # Wayland is the active windowing system
        add_executable(HelloWorld.Wayland
                Linux/HelloWorld_Linux_Wayland.cpp
                Linux/WaylandParent.h
                ${SHARED_SOURCE}
        )
        target_link_libraries(HelloWorld.Wayland PRIVATE Fuse)
    elseif (DEFINED ENV{DISPLAY})
        # X11 is the active windowing system
        add_executable(HelloWorld.X11
                Linux/HelloWorld_Linux_X11.cpp
                Linux/X11Parent.h
                ${SHARED_SOURCE}
        )
        target_link_libraries(HelloWorld.X11 PRIVATE Fuse)
    else ()
        message(FATAL_ERROR "No active windowing system detected")
    endif ()
elseif (APPLE)
    add_executable(HelloWorld.Apple
            ${SHARED_SOURCE}
    )
    target_link_libraries(HelloWorld.Apple PRIVATE Fuse)
endif ()