// Author: Jake Rieger
// Created: 7/11/2024.
//

#include "CairoBackend.h"

#include "Platform/X11PluginView.h"

#include <cassert>

namespace Fuse {
    void CairoBackend::OnResize(const Size<u32>& size) {
        m_Surface->set_size(static_cast<int>(size.Width), static_cast<int>(size.Height));
    }

    void CairoBackend::Initialize(IPluginView* owner) {
        IBackend::Initialize(owner);
        if (!m_OwningView) {
            throw std::runtime_error(
              "CairoBackend::Initialize: m_OwningView is null. Ensure IBackend::Initialize(owner) "
              "was called first.");
        }

        m_Context.reset();
        m_Surface.reset();
        const auto view  = m_OwningView->As<X11PluginView>();
        const int screen = DefaultScreen(view->GetDisplay());

        m_Surface = Cairo::XlibSurface::create(view->GetDisplay(),
                                               view->GetWindow(),
                                               DefaultVisual(view->GetDisplay(), screen),
                                               static_cast<i32>(view->GetSize().Width),
                                               static_cast<i32>(view->GetSize().Height));

        if (!m_Surface) {
            throw std::runtime_error("Failed to create Cairo surface");
        }

        m_Context = Cairo::Context::create(m_Surface);

        if (!m_Context) {
            throw std::runtime_error("Failed to create Cairo context");
        }
    }

    void CairoBackend::BeginDrawing(Color clearColor) {
        m_Context->set_source_rgba(clearColor.Red(),
                                   clearColor.Green(),
                                   clearColor.Blue(),
                                   clearColor.Alpha());
        m_Context->paint();
    }

    void CairoBackend::EndDrawing() {
        IBackend::EndDrawing();
    }

    void
    CairoBackend::DrawRect(const Size<u32>& size, const Offset& position, const Color& fillColor) {
        m_Context->set_source_rgba(fillColor.Red(),
                                   fillColor.Green(),
                                   fillColor.Blue(),
                                   fillColor.Alpha());
        m_Context->rectangle(position.X, position.Y, size.Width, size.Height);
        m_Context->fill();
    }

    void CairoBackend::DrawLine() {
        IBackend::DrawLine();
    }

    void CairoBackend::DrawEllipse() {
        IBackend::DrawEllipse();
    }

    void CairoBackend::DrawPath() {
        IBackend::DrawPath();
    }

    void CairoBackend::DrawString() {
        IBackend::DrawString();
    }

    void CairoBackend::Shutdown() {
        m_Context.reset();
        m_Surface.reset();
    }
}  // namespace Fuse