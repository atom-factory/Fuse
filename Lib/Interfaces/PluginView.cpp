// Author: Jake Rieger
// Created: 7/12/2024.
//

#include "Platform/Platform.h"
#include "PluginView.h"
#include "PluginCanvas.h"

#include <queue>

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
    void IPluginView::OnPaint() {
        if (const auto backend = GetBackend()) {
            if (m_OwningCanvas) {
                // Clear drawing area (canvas) with our specified background color
                backend->BeginDrawing(m_OwningCanvas->BackgroundColor);

                // Draw our component tree starting with the root returned from
                // IPluginCanvas::Draw() using a breadth-first search
                {
                    const auto dimension = Dimension(m_ViewState.Size);
                    const auto root      = m_OwningCanvas->Draw(this, dimension);
                    std::queue<IComponent*> queue;
                    queue.push(root);

                    while (!queue.empty()) {
                        IComponent* component = queue.front();
                        queue.pop();

                        component->Draw(backend);

                        auto result = component->GetChildren();
                        if (result.has_value()) {
                            auto children = result.value();
                            for (const auto& child : children) {
                                queue.push(child);
                            }
                        }
                    }
                }

                backend->EndDrawing();
            }
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