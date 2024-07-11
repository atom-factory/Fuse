// Author: Jake Rieger
// Created: 7/11/24.
//

#include "X11AppWindow.h"

#include <cstring>
#include <iostream>

namespace ArkVector {
    void X11AppWindow::Initialize(void* parent) {
        m_pDisplay = XOpenDisplay(nullptr);
        if (!m_pDisplay) {
            std::cerr << "Unable to open X display" << std::endl;
            return;
        }

        m_Screen = DefaultScreen(m_pDisplay);

        Window* parentWindow = nullptr;
        if (parent) {
            parentWindow = (Window*)parent;
        }
        m_Window = XCreateSimpleWindow(m_pDisplay,
                                       parent ? *parentWindow : RootWindow(m_pDisplay, m_Screen),
                                       10,
                                       10,
                                       m_WindowSize.Width,
                                       m_WindowSize.Height,
                                       1,
                                       BlackPixel(m_pDisplay, m_Screen),
                                       WhitePixel(m_pDisplay, m_Screen));
        XStoreName(m_pDisplay, m_Window, "X11 Window - ArkVector");
        XSelectInput(m_pDisplay, m_Window, ExposureMask | KeyPressMask | StructureNotifyMask);
        XMapWindow(m_pDisplay, m_Window);
    }

    void X11AppWindow::Run() {
        XColor color;
        const Colormap colormap = DefaultColormap(m_pDisplay, m_Screen);
        XParseColor(m_pDisplay, colormap, "#00AAFF", &color);
        XAllocColor(m_pDisplay, colormap, &color);

        for (;;) {
            XNextEvent(m_pDisplay, &m_Event);

            switch (m_Event.type) {
                case Expose: {
                    XSetForeground(m_pDisplay, DefaultGC(m_pDisplay, m_Screen), color.pixel);
                    XFillRectangle(m_pDisplay,
                                   m_Window,
                                   DefaultGC(m_pDisplay, m_Screen),
                                   0,
                                   0,
                                   m_WindowSize.Width,
                                   m_WindowSize.Height);
                } break;
                case ConfigureNotify: {
                    const auto newWidth  = m_Event.xconfigure.width;
                    const auto newHeight = m_Event.xconfigure.height;
                    m_WindowSize.Width   = newWidth;
                    m_WindowSize.Height  = newHeight;
                    XFillRectangle(m_pDisplay,
                                   m_Window,
                                   DefaultGC(m_pDisplay, m_Screen),
                                   0,
                                   0,
                                   m_WindowSize.Width,
                                   m_WindowSize.Height);
                } break;
                case KeyPress: {
                    // Close window on key press
                    return;
                }
                case DestroyNotify: {
                } break;
                default:
                    break;
            }
        }
    }

    void X11AppWindow::Shutdown() {
        XCloseDisplay(m_pDisplay);
    }
}  // namespace ArkVector