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

namespace Fuse {
    void IPluginView::OnPaint(const Color& backgroundColor) const {
        const auto backend = GetBackend();
        backend->BeginDrawing(backgroundColor);

        const auto root = m_OwningCanvas->Draw();
        if (root) {
            root->Draw(backend);
        }

        backend->EndDrawing();
    }

    IPluginView* IPluginView::Create(void* parent) {
#if defined(PLATFORM_WINDOWS)
        return new Win32PluginView(static_cast<HWND>(parent));
#elif defined(PLATFORM_LINUX)
        return new X11AppWindow(windowSize);
#elif defined(PLATFORM_APPLE)
        return nullptr;
#endif

        return nullptr;
    }

}  // namespace Fuse