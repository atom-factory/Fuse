// Author: Jake Rieger
// Created: 7/16/24.
//

#pragma once

#include "Platform/Platform.h"
#include "Platform/X11PluginView.h"

namespace X11Parent {
    inline Display* g_Display = nullptr;
    inline int g_Screen       = -1;
    inline Window g_Window;
    inline Fuse::X11PluginView* g_View = nullptr;

    inline int CreateParentWindow() {
        g_Display = XOpenDisplay(nullptr);
        if (!g_Display) {
            fprintf(stderr, "Failed to open X display\n");
            return EXIT_FAILURE;
        }

        g_Screen = DefaultScreen(g_Display);

        const Window rootWindow = RootWindow(g_Display, g_Screen);
        g_Window                = XCreateSimpleWindow(g_Display,
                                       rootWindow,
                                       0,
                                       0,
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

    inline void Run() {
        XEvent event;
        bool running = true;
        while (running) {
            XNextEvent(g_Display, &event);

            switch (event.type) {
                case Expose: {
                    // Redraw the window
                    if (g_View) {
                        g_View->OnPaint(Fuse::Color(0xFF01030C));
                    }
                } break;
                case KeyPress:
                    break;
                case DestroyNotify:
                    running = false;
                    break;
                case ConfigureNotify: {
                    // Update window sizes
                    const XConfigureEvent xce = event.xconfigure;
                    if (xce.window == g_Window) {
                        const auto width  = static_cast<u32>(xce.width);
                        const auto height = static_cast<u32>(xce.height);
                        if (g_View) {
                            g_View->OnResize({width, height});
                        }
                    }
                } break;
                default:
                    break;
            }
        }
    }

    inline void DestroyParentWindow() {
        XDestroyWindow(g_Display, g_Window);
        XCloseDisplay(g_Display);
    }
}  // namespace X11Parent