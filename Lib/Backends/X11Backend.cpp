// Author: Jake Rieger
// Created: 7/11/2024.
//

#include "X11Backend.h"

#include <cassert>

namespace ArkVector {
    void X11Backend::Init(Display* pDisplay,
                          const Window window,
                          const i32 screen,
                          const Size<u32>& size) {
        m_pContext.reset();
        m_pSurface.reset();

        m_pSurface = Cairo::XlibSurface::create(pDisplay,
                                                window,
                                                DefaultVisual(pDisplay, screen),
                                                static_cast<int>(size.Width),
                                                static_cast<int>(size.Height));
        if (!m_pSurface) {
            printf("Failed to create Cairo surface");
            return;
        }

        m_pContext = Cairo::Context::create(m_pSurface);

        if (!m_pContext) {
            printf("Failed to create Cairo context");
        }
    }

    void X11Backend::Shutdown() {
        m_pContext.reset();
        m_pSurface.reset();
    }

    void X11Backend::OnResize(const Size<u32>& size) {
        m_pSurface->set_size(static_cast<int>(size.Width), static_cast<int>(size.Height));
    }

    void X11Backend::OnPaint(const Size<u32>& size) {
        assert(m_pContext && "Cairo context invalid");
        assert(m_pSurface && "Cairo context invalid");

        m_pContext->set_source_rgb(0.0, 0.5, 1.0);
        m_pContext->rectangle(0, 0, size.Width, size.Height);
        m_pContext->fill();
    }
}  // namespace ArkVector