// Author: Jake Rieger
// Created: 7/12/2024.
//

#include "Platform/Platform.h"
#include "PluginView.h"
#include "PluginCanvas.h"

#if defined(PLATFORM_WINDOWS)
    #include "Platform/Win32PluginView.h"
#elif defined(PLATFORM_LINUX)
    #include "Platform/X11PluginView.h"
#elif defined(PLATFORM_APPLE)
    #include "Platform/NSAPluginView.h"
#endif

namespace ArkVector {
    void IPluginView::OnPaint() const {
        auto root = m_OwningCanvas->Draw();
    }

    IPluginView* IPluginView::Create(const Size<u32>& windowSize) {
#if defined(PLATFORM_WINDOWS)
        return new Win32PluginView(windowSize);
#elif defined(PLATFORM_LINUX)
        return new X11AppWindow(windowSize);
#elif defined(PLATFORM_APPLE)
        return nullptr;
#endif

        return nullptr;
    }

}  // namespace ArkVector