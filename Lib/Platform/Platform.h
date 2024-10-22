// Author: Jake Rieger
// Created: 7/10/2024.
//

#pragma once

#include <stdexcept>

#if defined(_WIN32) || defined(_WIN64)
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX
    #pragma comment(lib, "d2d1.lib")
    #pragma comment(lib, "dwrite.lib")

    #include <Windows.h>
    #include <windowsx.h>
    #include <d2d1.h>
    #include <dwrite.h>

/**
 * @brief Prints debug message to debugger console when app runs in WIN32 mode
 */
inline void DebugPrint(const char* fmt, ...) {
    char buffer[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    OutputDebugStringA(buffer);
}

template<class Interface>
void SafeRelease(Interface** ppInterface) {
    if (*ppInterface != NULL) {
        (*ppInterface)->Release();
        (*ppInterface) = NULL;
    }
}

/**
 * @brief Throws runtime error with message if HRESULT failed
 *
 * @param hr HRESULT
 * @param msg Error message to display if result failed
 */
inline void CheckResult(const HRESULT hr, const char* msg) {
    if (FAILED(hr)) {
        throw std::runtime_error(msg);
    }
}
#elif defined(__linux__)
    #include <cairomm/cairomm.h>
    #include <cairomm/refptr.h>
    #include <cairomm/context.h>
    #if defined(USE_WAYLAND)
        #include <wayland-client.h>
        #include <wayland-egl.h>
        #include <EGL/egl.h>
    #elif defined(USE_X11)
        #include <X11/Xlib.h>
        #include <cairomm/xlib_surface.h>

inline Display* GetDisplayFromWindow(const Window* window) {
    Display* display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        fprintf(stderr, "Unable to open X display.\n");
        return nullptr;
    }

    XWindowAttributes windowAttribs;
    if (XGetWindowAttributes(display, *window, &windowAttribs) == 0) {
        fprintf(stderr, "Unable to get window attributes.\n");
        XCloseDisplay(display);
        return nullptr;
    }

    return display;
}
    #endif
#elif defined(__APPLE__)
#endif

/**
 * @brief Throws runtime error with message if pointer is nullptr.
 */
inline void CheckNull(const void* ptr, const char* msg) {
    if (ptr == nullptr) {
        throw std::runtime_error(msg);
    }
}