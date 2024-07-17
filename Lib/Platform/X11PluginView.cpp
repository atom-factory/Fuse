// Author: Jake Rieger
// Created: 7/11/24.
//

#include "X11PluginView.h"

namespace Fuse {
    void X11PluginView::Initialize() {
        m_Display = XOpenDisplay(nullptr);
        if (!m_Display) {
            throw std::runtime_error("Failed to open X display.");
        }

        const int screen  = DefaultScreen(m_Display);
        const auto parent = static_cast<Window*>(m_Parent);

        XSetWindowAttributes childAttributes;
        childAttributes.background_pixel = WhitePixel(m_Display, screen);  // Background color
        childAttributes.event_mask = ExposureMask | KeyPressMask;  // Event mask for child window

        m_Window = XCreateWindow(m_Display,
                                 *parent,
                                 0,
                                 0,
                                 m_WindowSize.Width,
                                 m_WindowSize.Height,
                                 1,
                                 CopyFromParent,
                                 InputOutput,
                                 nullptr,
                                 CWBackPixel | CWEventMask,
                                 &childAttributes);

        XMapWindow(m_Display, m_Window);
    }

    void X11PluginView::Shutdown() {
        XDestroyWindow(m_Display, m_Window);
    }

    void X11PluginView::OnResize(const Size<u32>& newSize) {
        IPluginView::OnResize(newSize);
    }
}  // namespace Fuse