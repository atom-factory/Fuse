// Author: Jake Rieger
// Created: 7/11/2024.
//

#pragma once

#include "Backend.h"
#include "Platform/X11AppWindow.h"

#include <cairomm/context.h>
#include <cairomm/refptr.h>
#include <cairomm/xlib_surface.h>

namespace ArkVector {
    class X11Backend final : public IBackend {
    public:
        void Init(Display* pDisplay, Window window, i32 screen, const Size<u32>& size);
        void Shutdown() override;
        void OnResize(const Size<u32>& size) override;
        void OnPaint(const Size<u32>& size) override;

    private:
        Cairo::RefPtr<Cairo::XlibSurface> m_pSurface;
        Cairo::RefPtr<Cairo::Context> m_pContext;
    };
}  // namespace ArkVector
