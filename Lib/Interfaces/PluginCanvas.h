// Author: Jake Rieger
// Created: 7/12/2024.
//

#pragma once

#include "Platform/Platform.h"
#include "Component.h"
#include "PluginView.h"
#include "Traits.h"

#if defined(PLATFORM_WINDOWS)
    #include "Platform/Win32PluginView.h"
#elif defined(PLATFORM_LINUX)
    #include "Platform/X11PluginView.h"
#elif defined(PLATFORM_APPLE)
    #include "Platform/NSPluginView.h"
#endif

namespace Fuse {
    /**
     * @brief Root interface of an Fuse-rendered plugin.
     *
     * The constructor takes a void ptr to the parent window handle (`HWND` on Windows, `Window` on
     * X11, etc.)
     *
     * Example Implementation:
     * @code{.cpp}
     * class MyCanvas final : public IPluginCanvas {
     * public:
     *     explicit MyCanvas(void* parent) : IPluginCanvas(parent) {
     *         this->BackgroundColor = Color(0xFF000000); // black background
     *         this->IPluginCanvas::AttachToParent(parent); // attach canvas to parent
     *     }
     *     IComponent* Draw() override;
     * };
     * @endcode
     */
    class IPluginCanvas : public Traits::TNotify {
    public:
        explicit IPluginCanvas(void* parent) {
            m_View = IPluginView::Create(parent);
            if (!m_View) {
                throw std::runtime_error("Failed to create plugin view");
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

        Color BackgroundColor;

    protected:
        IPluginView* m_View;
    };
} // namespace Fuse