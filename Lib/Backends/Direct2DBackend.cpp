// Author: Jake Rieger
// Created: 7/11/2024.
//

#include "Direct2DBackend.h"

#include "Interfaces/PluginView.h"
#include "Platform/Win32PluginView.h"

namespace ArkVector {
    void Direct2DBackend::Init() {
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

    void Direct2DBackend::OnResize(const Size<u32>& size) {}

    void Direct2DBackend::DrawRect() {
        ID2D1SolidColorBrush* brush = nullptr;
        auto hr = m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &brush);
        if (FAILED(hr)) {
            throw std::runtime_error("Failed to create brush");
        }

        auto view = m_OwningView->As<Win32PluginView>();
        RECT rc;
        ::GetClientRect(view->GetHandle(), &rc);
        D2D1_RECT_F rect = D2D1::RectF(static_cast<FLOAT>(rc.left + 100),
                                       static_cast<FLOAT>(rc.top + 100),
                                       static_cast<FLOAT>(rc.right - 100),
                                       static_cast<FLOAT>(rc.bottom - 100));

        m_RenderTarget->BeginDraw();
        m_RenderTarget->DrawRectangle(&rect, brush);

        hr = m_RenderTarget->EndDraw();
        if (FAILED(hr)) {
            throw std::runtime_error("Failed to draw render target");
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
}  // namespace ArkVector