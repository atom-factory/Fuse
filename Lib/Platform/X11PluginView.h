// Author: Jake Rieger
// Created: 7/11/24.
//

#pragma once

#include "PluginView.h"
#include "Platform.h"

namespace Fuse {
    class X11PluginView final : public IPluginView {
    public:
        explicit X11PluginView(const Size<u32>& windowSize)
            : IPluginView(windowSize), m_pDisplay(nullptr) {}

        void Initialize(Display* display, Window parent, i32 screen);
        void OnResize() const;
        void OnPaint() const;

        [[nodiscard]] Display* GetDisplay() const {
            return m_pDisplay;
        }

        Window& GetWindow() {
            return m_Window;
        }

        [[nodiscard]] int GetScreen() const {
            return m_Screen;
        }

    protected:
        void Shutdown() override;

    private:
        Display* m_pDisplay;
        Window m_Window {};
        XEvent m_Event {};
        int m_Screen {};
    };

}  // namespace Fuse
