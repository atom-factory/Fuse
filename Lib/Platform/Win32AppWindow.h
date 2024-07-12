// Author: Jake Rieger
// Created: 7/11/2024.
//

#pragma once

#include "Platform.h"
#include "AppWindow.h"

namespace ArkVector {
    class Win32AppWindow final : public IAppWindow {
    public:
        explicit Win32AppWindow(const Size<u32>& windowSize) : IAppWindow(windowSize) {}

        void Initialize(HWND parent, int nCmdShow);
        void Shutdown() override;

        static LRESULT CALLBACK MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    private:
        HWND m_Handle        = nullptr;
        HINSTANCE m_Instance = nullptr;
    };
}  // namespace ArkVector