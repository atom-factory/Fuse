// Author: Jake Rieger
// Created: 7/11/2024.
//

#include "Direct2DBackend.h"

#include "Color.h"
#include "Interfaces/PluginView.h"
#include "Platform/Win32PluginView.h"
#include "Stroke.h"

namespace Fuse {
    void Direct2DBackend::Initialize(IPluginView* owner) {
        IBackend::Initialize(owner);

        CheckNull(m_OwningView,
                  "Direct2DBackend::Initialize: m_OwningView is null. Ensure "
                  "IBackend::Initialize(owner) "
                  "was called first in the Initialize() method.");

        auto hr = ::D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_Factory);
        CheckResult(hr, "Failed to create Direct2D Factory");

        const auto view = m_OwningView->As<Win32PluginView>();
        RECT rc;
        ::GetClientRect(view->GetHandle(), &rc);
        hr = m_Factory->CreateHwndRenderTarget(
          D2D1::RenderTargetProperties(),
          D2D1::HwndRenderTargetProperties(view->GetHandle(),
                                           D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
          &m_RenderTarget);

        CheckResult(hr, "Failed to create render target");
    }

    void Direct2DBackend::OnResize(const Size<u32>& size) {
        if (m_RenderTarget) {
            const auto hr = m_RenderTarget->Resize(D2D1_SIZE_U(size.Width, size.Height));
            CheckResult(hr, "Failed to resize render target");
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
            CheckResult(m_RenderTarget->EndDraw(), "D2D EndDraw() method failed.");
        }
    }

    void Direct2DBackend::DrawRect(const Size<u32>& size,
                                   const Offset& position,
                                   const Color& fillColor,
                                   const Stroke& stroke,
                                   const bool rounded) {
        if (m_RenderTarget) {
            ID2D1SolidColorBrush* brush = nullptr;
            auto hr =
              m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(fillColor.Value()), &brush);
            CheckResult(hr, "Failed to create D2D brush.");

            const auto rect = D2D1::RectF(position.X,
                                          position.Y,
                                          static_cast<f32>(size.Width),
                                          static_cast<f32>(size.Height));

            m_RenderTarget->FillRectangle(rect, brush);

            if (stroke.Thickness > 0) {
                ID2D1SolidColorBrush* strokeBrush = nullptr;
                hr = m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(stroke.Color.Value()),
                                                           &strokeBrush);
                CheckResult(hr, "Failed to create D2D brush.");
                m_RenderTarget->DrawRectangle(rect, strokeBrush, stroke.Thickness, nullptr);
            }
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