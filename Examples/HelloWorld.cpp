// Author: Jake Rieger
// Created: 7/10/2024.
//

#include "Platform.h"
#include "Platform/AppWindow.h"
#include <X11/Xlib.h>

#if defined(PLATFORM_WINDOWS)
    #include "Platform/Win32AppWindow.h"
#elif defined(PLATFORM_LINUX)
    #include "Platform/X11AppWindow.h"
#elif defined(PLATFORM_APPLE)
#endif

int main() {
    ArkVector::X11AppWindow* appWindow = nullptr;

    auto display = XOpenDisplay(nullptr);
    auto screen  = DefaultScreen(display);
    auto window  = XCreateSimpleWindow(display,
                                      RootWindow(display, screen),
                                      10,
                                      10,
                                      800,
                                      600,
                                      1,
                                      BlackPixel(display, screen),
                                      WhitePixel(display, screen));
    XSelectInput(display, window, ExposureMask | KeyPressMask | StructureNotifyMask);
    XMapWindow(display, window);

    appWindow = new ArkVector::X11AppWindow({800, 600});
    appWindow->Initialize(display, window, screen);

    XEvent event;
    for (;;) {
        XNextEvent(display, &event);

        switch (event.type) {
            case Expose: {
                appWindow->OnPaint();
            } break;
            case ConfigureNotify: {
                appWindow->OnResize();
            } break;
            case DestroyNotify: {
                XCloseDisplay(display);
            } break;
            default:
                break;
        }
    }

    return 0;
}

// #if defined(PLATFORM_WINDOWS)
//     appWindow = new ArkVector::Win32AppWindow({800, 600});
// #elif defined(PLATFORM_LINUX)
//     appWindow = new ArkVector::X11AppWindow({800, 600});
// #elif defined(PLATFORM_APPLE)
//     appWindow = nullptr;
// #endif
//
//     appWindow->Initialize(nullptr);
//     appWindow->Run();
//     delete appWindow;
