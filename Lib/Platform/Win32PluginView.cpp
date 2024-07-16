// Author: Jake Rieger
// Created: 7/11/2024.
//

#include "Win32PluginView.h"
#include "Backends/Direct2DBackend.h"

#include <cassert>

namespace ArkVector {
    void Win32PluginView::Initialize(HWND parent, int nCmdShow) {
        RECT rc;
        ::GetClientRect(parent, &rc);
        m_WindowSize.Width  = rc.right - rc.left;
        m_WindowSize.Height = rc.bottom - rc.top;

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
                                     static_cast<i32>(m_WindowSize.Width),
                                     static_cast<i32>(m_WindowSize.Height),
                                     parent,
                                     nullptr,
                                     m_Instance,
                                     this);

        if (!m_Handle) {
            throw std::runtime_error("Failed to create window.");
        }

        ::SetWindowLongPtrA(m_Handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

        m_Backend = new Direct2DBackend;
        m_Backend->SetOwner(this);
        m_Backend->Init();

        ::ShowWindow(m_Handle, nCmdShow);
        ::UpdateWindow(m_Handle);
    }

    void Win32PluginView::Shutdown() {
        // TODO: cleanup backend ptr or make unique
        // if (m_Backend) {
        //     m_Backend = nullptr;
        // }
        if (m_Handle) {
            ::DestroyWindow(m_Handle);
            m_Handle = nullptr;
        }
    }

    void Win32PluginView::OnResize(const Size<u32>& newSize) {
        IPluginView::OnResize(newSize);
        if (m_Handle) {
            ::SetWindowPos(m_Handle,
                           nullptr,
                           0,
                           0,
                           newSize.Width,
                           newSize.Height,
                           SWP_NOZORDER | SWP_NOACTIVATE);
        }
        m_Backend->OnResize(newSize);
    }

    LRESULT Win32PluginView::MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        const LONG_PTR userData = ::GetWindowLongPtrA(hwnd, GWLP_USERDATA);
        const auto view         = reinterpret_cast<Win32PluginView*>(userData);

        if (!view) {
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }

        switch (msg) {
            case WM_DESTROY:
            case WM_CLOSE:
                view->m_Handle = nullptr;
                return 0;
            case WM_PAINT: {
                view->OnPaint(Color(0xFF1A1C29));
                return 0;
            }
            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }
}  // namespace ArkVector