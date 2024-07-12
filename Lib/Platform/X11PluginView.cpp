// Author: Jake Rieger
// Created: 7/11/24.
//

#include "X11PluginView.h"

#include "Backends/Backend.h"
#include "Backends/X11Backend.h"

#include <cstring>
#include <iostream>

namespace ArkVector {
    X11Backend* g_Backend;

    void X11PluginView::Initialize(Display* display, const Window parent, const i32 screen) {
        m_pDisplay = display;
        if (!m_pDisplay) {
            std::cerr << "Unable to open X display" << std::endl;
            return;
        }

        m_Screen = screen;

        XSetWindowAttributes childAttrs;
        childAttrs.background_pixel = WhitePixel(m_pDisplay, m_Screen);
        childAttrs.event_mask       = ExposureMask | KeyPressMask;
        m_Window                    = XCreateWindow(m_pDisplay,
                                 parent,
                                 0,
                                 0,
                                 m_WindowSize.Width,
                                 m_WindowSize.Height,
                                 0,
                                 CopyFromParent,
                                 InputOutput,
                                 CopyFromParent,
                                 CWBackPixel | CWEventMask,
                                 &childAttrs);

        XStoreName(m_pDisplay, m_Window, "X11 Window - ArkVector");
        XSelectInput(m_pDisplay, m_Window, ExposureMask | KeyPressMask);
        XMapWindow(m_pDisplay, m_Window);

        g_Backend = new X11Backend();
        g_Backend->Init(m_pDisplay, m_Window, m_Screen, m_WindowSize);
    }

    void X11PluginView::OnResize() const {
        g_Backend->OnResize(m_WindowSize);
    }

    void X11PluginView::OnPaint() const {
        g_Backend->OnPaint(m_WindowSize);
    }

    void X11PluginView::Shutdown() {
        g_Backend->Shutdown();
        delete g_Backend;
        XCloseDisplay(m_pDisplay);
    }
}  // namespace ArkVector