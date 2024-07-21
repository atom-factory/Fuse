// Author: Jake Rieger
// Created: 7/11/24.
//

#include "X11PluginView.h"
#include "Backends/CairoBackend.h"

namespace Fuse {
    void X11PluginView::Initialize() {
        if (m_Display == nullptr) {
            m_Display = XOpenDisplay(nullptr);
        }

        m_Screen = DefaultScreen(m_Display);

        XSetWindowAttributes childAttributes;
        childAttributes.background_pixel = WhitePixel(m_Display, m_Screen);  // Background color
        childAttributes.event_mask =
          ExposureMask | KeyPressMask | StructureNotifyMask;  // Event mask for child window

        auto parent = *(Window*)m_Parent;
        XWindowAttributes parentAttributes;
        if (XGetWindowAttributes(m_Display, parent, &parentAttributes) == 0) {
            throw std::runtime_error("Failed to get parent X window attributes.");
        }
        m_WindowSize.Set(parentAttributes.width, parentAttributes.height);

        m_Window = XCreateWindow(m_Display,
                                 *(Window*)m_Parent,
                                 0,
                                 0,
                                 m_WindowSize.Width,
                                 m_WindowSize.Height,
                                 0,
                                 CopyFromParent,
                                 InputOutput,
                                 CopyFromParent,
                                 CWBackPixel | CWEventMask,
                                 &childAttributes);

        XStoreName(m_Display, m_Window, "X11 Window - Fuse");
        XSelectInput(m_Display, m_Window, ExposureMask | KeyPressMask | StructureNotifyMask);
        XMapWindow(m_Display, m_Window);

        m_Backend = new CairoBackend();
        m_Backend->Initialize(this);

        this->m_ActiveView = this;
    }

    void X11PluginView::Shutdown() {
        XDestroyWindow(m_Display, m_Window);
    }

    void X11PluginView::OnResize(const Size<u32>& newSize) {
        IPluginView::OnResize(newSize);
        m_Backend->OnResize(newSize);
    }
}  // namespace Fuse