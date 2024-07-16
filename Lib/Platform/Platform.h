// Author: Jake Rieger
// Created: 7/10/2024.
//

#pragma once

#include <exception>

#if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX
    #pragma comment(lib, "d2d1.lib")
    #pragma comment(lib, "dwrite.lib")

    #include <Windows.h>
    #include <d2d1.h>
    #include <dwrite.h>

template<class Interface>
void SafeRelease(Interface** ppInterface) {
    if (*ppInterface != NULL) {
        (*ppInterface)->Release();
        (*ppInterface) = NULL;
    }
}
#elif defined(__linux__)
#include <cairomm/cairomm.h>
#if defined(USE_WAYLAND)
#include <wayland-client.h>
#include <wayland-egl.h>
#include <EGL/egl.h>
#elif defined(USE_X11)
#include <X11/Xlib.h>
#endif
#elif defined(__APPLE__)
    #define PLATFORM_APPLE
#endif
