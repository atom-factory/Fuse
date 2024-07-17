// Author: Jake Rieger
// Created: 7/11/24.
//

#pragma once

#include "Platform.h"
#include "Interfaces/PluginView.h"

namespace Fuse {
    class X11PluginView final : public IPluginView {
    public:
        explicit X11PluginView(Window* parent) : IPluginView(parent) {}

        void Initialize() override;
        void Shutdown() override;
        void OnResize(const Size<u32>& newSize) override;

        [[nodiscard]] Window GetWindow() const {
            return m_Window;
        }

        [[nodiscard]] Display* GetDisplay() const {
            return m_Display;
        }

    private:
        Window m_Window    = {};
        Display* m_Display = nullptr;
        // XEvent m_Event     = {};
    };

}  // namespace Fuse
