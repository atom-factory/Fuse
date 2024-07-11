// Author: Jake Rieger
// Created: 7/11/24.
//

#pragma once

#include "AppWindow.h"
#include <X11/Xlib.h>

namespace ArkVector {
    class X11AppWindow final : public IAppWindow {
    public:
        explicit X11AppWindow(const Size<u32>& windowSize)
            : IAppWindow(windowSize), m_pDisplay(nullptr) {}

        void Initialize(void* parent) override;
        void Run() override;
        void Shutdown() override;

        [[nodiscard]] Display* GetDisplay() const {
            return m_pDisplay;
        }

        Window& GetWindow() {
            return m_Window;
        }

    private:
        Display* m_pDisplay;
        Window m_Window {};
        XEvent m_Event {};
        int m_Screen {};
    };

}  // namespace ArkVector
