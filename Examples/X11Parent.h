// Author: Jake Rieger
// Created: 7/16/24.
//

#pragma once

#include "Platform/Platform.h"

namespace X11Parent {
    static Display* g_Display = nullptr;
    static int g_Screen       = -1;
    static Window g_Window;

    static int CreateParentWindow() {
        g_Display = XOpenDisplay(nullptr);
        if (!g_Display) {
            fprintf(stderr, "Failed to open X display\n");
            return EXIT_FAILURE;
        }

        g_Screen = DefaultScreen(g_Display);

        const Window rootWindow = RootWindow(g_Display, g_Screen);
        g_Window                = XCreateSimpleWindow(g_Display,
                                       rootWindow,
                                       100,
                                       100,
                                       600,
                                       300,
                                       1,
                                       BlackPixel(g_Display, g_Screen),
                                       WhitePixel(g_Display, g_Screen));

        XSelectInput(g_Display, g_Window, ExposureMask | KeyPressMask | StructureNotifyMask);
        XStoreName(g_Display, g_Window, "X11 Window - Fuse");
        XMapWindow(g_Display, g_Window);

        return EXIT_SUCCESS;
    }

    static void Run() {
        XEvent event;
        bool running = true;
        while (running) {
            XNextEvent(g_Display, &event);

            switch (event.type) {
                case Expose:
                    // Redraw the window
                    break;
                case KeyPress:
                    break;
                case DestroyNotify:
                    running = false;
                    break;
                case ConfigureNotify:
                    // Update window sizes
                    break;
                default:
                    break;
            }
        }
    }

    static void DestroyParentWindow() {
        XDestroyWindow(g_Display, g_Window);
        XCloseDisplay(g_Display);
    }
}  // namespace X11Parent