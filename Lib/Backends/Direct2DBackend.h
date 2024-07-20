// Author: Jake Rieger
// Created: 7/11/2024.
//

#pragma once

#include "Platform/Platform.h"
#include "Interfaces/Backend.h"

namespace Fuse {
    class Direct2DBackend final : public IBackend {
    public:
        void Initialize(IPluginView* owner) override;
        void OnResize(const Size<u32>& size) override;

        void BeginDrawing(Color clearColor) override;
        void EndDrawing() override;

        void DrawRect(const Size<u32>& size,
                      const Offset& position,
                      const Color& fillColor,
                      const Stroke& stroke,
                      bool rounded) override;
        void DrawEllipse(f32 radius,
                         const Offset& position,
                         const Color& fillColor,
                         const Stroke& stroke) override;
        void DrawLine() override;
        void DrawPath(const Offset& position,
                      Vector<Offset> points,
                      const Color& fillColor,
                      const Stroke& stroke) override;
        void DrawString() override;

    protected:
        void Shutdown() override;

    private:
        ID2D1Factory* m_Factory               = nullptr;
        ID2D1HwndRenderTarget* m_RenderTarget = nullptr;

        RECT PrivateGetClientRect() const;
        static Vector<D2D1_POINT_2F> PrivateOffsetVecToD2DPointVec(const Vector<Offset>& points);
    };
}  // namespace Fuse
