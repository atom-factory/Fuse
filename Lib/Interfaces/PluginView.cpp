// Author: Jake Rieger
// Created: 7/12/2024.
//

#include "Platform/Platform.h"
#include "PluginView.h"
#include "PluginCanvas.h"

#if defined(PLATFORM_WINDOWS)
    #include "Platform/Win32PluginView.h"
#elif defined(PLATFORM_LINUX)
    #if defined(USE_X11)
        #include "Platform/X11PluginView.h"
    #elif defined(USE_WAYLAND)
        #include "Platform/WaylandPluginView.h"
    #endif
#elif defined(PLATFORM_APPLE)
    #include "Platform/NSAPluginView.h"
#endif

namespace Fuse {
    void IPluginView::OnPaint(const Color& backgroundColor) const {
        if (const auto backend = GetBackend()) {
            backend->BeginDrawing(backgroundColor);

            if (m_OwningCanvas) {
                const auto root = m_OwningCanvas->Draw();
                if (root) {
                    root->Draw(backend);
                }
            }

            backend->EndDrawing();
        }
    }

    IPluginView* IPluginView::Create(void* parent) {
#if defined(PLATFORM_WINDOWS)
        return new Win32PluginView(static_cast<HWND>(parent));
#elif defined(PLATFORM_LINUX)
    #if defined(USE_X11)
        return new X11PluginView((Window*)parent, nullptr);
    #elif defined(USE_WAYLAND)
        return new WaylandPluginView(nullptr);
    #endif
#elif defined(PLATFORM_APPLE)
        return nullptr;
#endif
        return nullptr;
    }

}  // namespace Fuse