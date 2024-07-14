// Author: Jake Rieger
// Created: 7/12/2024.
//

#pragma once

#include "Platform/Platform.h"
#include "Component.h"
#include "PluginView.h"
#include "Trait.h"

#if defined(PLATFORM_WINDOWS)
    #include "Platform/Win32PluginView.h"
#elif defined(PLATFORM_LINUX)
    #include "Platform/X11PluginView.h"
#elif defined(PLATFORM_APPLE)
    #include "Platform/NSPluginView.h"
#endif

namespace ArkVector {
    /// Root interface of an ArkVector UI app
    class IPluginCanvas : public Trait::TNotify {
    public:
        IPluginCanvas() {
            m_View = IPluginView::Create({800, 600});
            if (!m_View) {
                throw std::exception("Failed to create plugin view");
            }
            m_View->SetOwner(this);
        }

        virtual ~IPluginCanvas() = default;

        virtual i32 AttachToParent(void* parent) {
#if defined(PLATFORM_WINDOWS)
            auto _parent = (HWND)parent;
            auto view    = m_View->As<Win32PluginView>();
            view->Initialize(_parent, SW_SHOW);
            return 0;
#elif defined(PLATFORM_LINUX)
#elif defined(PLATFORM_APPLE)
#endif

            return -1;
        }

        virtual IComponent* Draw() = 0;

        [[nodiscard]] IPluginView* GetView() const {
            return m_View;
        }

        [[nodiscard]] IBackend* GetBackend() const {
            return m_View->GetBackend();
        }

    protected:
        IPluginView* m_View;
    };
}  // namespace ArkVector