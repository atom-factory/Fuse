// Author: Jake Rieger
// Created: 7/11/2024.
//

#include "Direct2DBackend.h"

#include "Color.h"
#include "Interfaces/PluginView.h"
#include "Platform/Win32PluginView.h"

namespace Fuse {
    void Direct2DBackend::Init() {
        if (!m_OwningView) {
            throw std::runtime_error(
              "Direct2DBackend::Init: m_OwningView is null. Ensure SetOwner() "
              "was called before initializing.");
        }

        auto hr = ::D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_Factory);
        if (FAILED(hr)) {
            throw std::runtime_error("Failed to create Direct2D Factory");
        }

        auto view = m_OwningView->As<Win32PluginView>();
        RECT rc;
        ::GetClientRect(view->GetHandle(), &rc);
        hr = m_Factory->CreateHwndRenderTarget(
          D2D1::RenderTargetProperties(),
          D2D1::HwndRenderTargetProperties(view->GetHandle(),
                                           D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
          &m_RenderTarget);

        if (FAILED(hr)) {
            throw std::runtime_error("Failed to create render target");
        }
    }

    void Direct2DBackend::OnResize(const Size<u32>& size) {
        if (m_RenderTarget) {
            auto hr = m_RenderTarget->Resize(D2D1_SIZE_U(size.Width, size.Height));
            if (FAILED(hr)) {
                throw std::runtime_error("Failed to resize render target");
            }
        }
    }

    void Direct2DBackend::BeginDrawing(const Color clearColor) {
        if (m_RenderTarget) {
            m_RenderTarget->BeginDraw();
            m_RenderTarget->Clear(D2D1::ColorF(clearColor.Value()));
        }
    }

    void Direct2DBackend::EndDrawing() {
        if (m_RenderTarget) {
            m_RenderTarget->EndDraw();
        }
    }

    void Direct2DBackend::DrawRect(const Size<u32>& size,
                                   const Offset& position,
                                   const Color& fillColor) {
        if (m_RenderTarget) {
            ID2D1SolidColorBrush* brush = nullptr;
            auto hr =
              m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(fillColor.Value()), &brush);

            m_RenderTarget->FillRectangle(D2D1::RectF(position.X,
                                                      position.Y,
                                                      static_cast<f32>(size.Width),
                                                      static_cast<f32>(size.Height)),
                                          brush);
        }
    }

    void Direct2DBackend::DrawEllipse() {}

    void Direct2DBackend::DrawLine() {}

    void Direct2DBackend::DrawPath() {}

    void Direct2DBackend::DrawString() {}

    void Direct2DBackend::Shutdown() {
        if (m_RenderTarget) {
            m_RenderTarget->Release();
            m_RenderTarget = nullptr;
        }
        if (m_Factory) {
            m_Factory->Release();
            m_Factory = nullptr;
        }
    }
}  // namespace Fuse