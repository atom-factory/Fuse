// Author: Jake Rieger
// Created: 7/11/2024.
//

#include "Win32AppWindow.h"

#include "Backends/Direct2DBackend.h"

#include <cassert>

namespace ArkVector {
    Direct2DBackend* g_Backend = nullptr;

    void Win32AppWindow::Initialize(const HWND parent, int nCmdShow) {
        m_Instance = ::GetModuleHandle(nullptr);

        WNDCLASSA wc     = {};
        wc.lpfnWndProc   = MessageHandler;
        wc.hInstance     = m_Instance;
        wc.lpszClassName = "ArkVectorHWNDChild";
        wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
        RegisterClassA(&wc);

        m_Handle = ::CreateWindowExA(0,
                                     "ArkVectorHWNDChild",
                                     "ArkVectorWindow",
                                     WS_CHILD | WS_VISIBLE,
                                     0,
                                     0,
                                     m_WindowSize.Width,
                                     m_WindowSize.Height,
                                     parent,
                                     nullptr,
                                     m_Instance,
                                     this);

        if (!m_Handle) {
            throw std::runtime_error("Failed to create window.");
        }

        ::SetWindowLongPtrA(m_Handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

        ::ShowWindow(m_Handle, nCmdShow);
        ::UpdateWindow(m_Handle);
    }

    void Win32AppWindow::Shutdown() {
        if (m_Handle) {
            ::DestroyWindow(m_Handle);
            m_Handle = nullptr;
        }
    }

    LRESULT Win32AppWindow::MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        const LONG_PTR userData = ::GetWindowLongPtrA(hwnd, GWLP_USERDATA);
        const auto appWindow    = reinterpret_cast<Win32AppWindow*>(userData);

        if (!appWindow) {
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }

        PAINTSTRUCT ps;
        HDC hdc;

        switch (msg) {
            case WM_DESTROY:
            case WM_CLOSE:
                appWindow->m_Handle = nullptr;
                return 0;
            case WM_SIZE: {
                const UINT width  = LOWORD(lParam);
                const UINT height = HIWORD(lParam);
                appWindow->m_WindowSize.Set(width, height);
                return 0;
            }
            case WM_PAINT: {
                hdc = BeginPaint(hwnd, &ps);

                // Set the background color to blue
                HBRUSH hBrush = CreateSolidBrush(RGB(0, 125, 255));
                FillRect(hdc, &ps.rcPaint, hBrush);

                DeleteObject(hBrush);
                EndPaint(hwnd, &ps);
                return 0;
            }
            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }
}  // namespace ArkVector