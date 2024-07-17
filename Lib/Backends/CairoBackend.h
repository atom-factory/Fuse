// Author: Jake Rieger
// Created: 7/11/2024.
//

#pragma once

#include "Platform/Platform.h"
#include "Interfaces/Backend.h"

namespace Fuse {
    class CairoBackend final : public IBackend {
    public:
        void OnResize(const Size<u32>& size) override;
        void Initialize(IPluginView* owner) override;
        void BeginDrawing(Color clearColor) override;
        void EndDrawing() override;
        void
        DrawRect(const Size<u32>& size, const Offset& position, const Color& fillColor) override;
        void DrawLine() override;
        void DrawEllipse() override;
        void DrawPath() override;
        void DrawString() override;

    protected:
        void Shutdown() override;

    private:
#if defined(USE_X11)
        Cairo::RefPtr<Cairo::XlibSurface> m_Surface;
#elif defined(USE_WAYLAND)
        Cairo::RefPtr<Cairo::EglSurface> m_Surface
#endif
        Cairo::RefPtr<Cairo::Context> m_Context;
    };
}  // namespace Fuse
