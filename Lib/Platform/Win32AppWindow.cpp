// Author: Jake Rieger
// Created: 7/11/2024.
//

#include "Win32AppWindow.h"

#include <cassert>

namespace ArkVector {
    void Win32AppWindow::Initialize() {
        m_Instance = ::GetModuleHandle(nullptr);

        WNDCLASSEXA wndClass;
        wndClass.style         = CS_HREDRAW | CS_VREDRAW;
        wndClass.lpfnWndProc   = MessageHandler;
        wndClass.cbClsExtra    = 0;
        wndClass.cbWndExtra    = 0;
        wndClass.hInstance     = m_Instance;
        wndClass.hIcon         = ::LoadIcon(nullptr, IDI_APPLICATION);
        wndClass.hIconSm       = wndClass.hIcon;
        wndClass.hCursor       = ::LoadCursor(nullptr, IDC_ARROW);
        wndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        wndClass.lpszMenuName  = nullptr;
        wndClass.lpszClassName = "ArkVectorWindowClass";
        wndClass.cbSize        = sizeof(WNDCLASSEXW);
        wndClass.cbWndExtra    = sizeof(Win32AppWindow);

        static ATOM registerResult = ::RegisterClassExA(&wndClass);
        assert(registerResult > 0 && "Window class registration failed");

        const u32 scrWidth  = ::GetSystemMetrics(SM_CXSCREEN);
        const u32 scrHeight = ::GetSystemMetrics(SM_CYSCREEN);
        const u32 posX      = (scrWidth - m_WindowSize.Width) / 2;
        const u32 posY      = (scrHeight - m_WindowSize.Height) / 2;

        m_Handle = ::CreateWindowExA(NULL,
                                     "ArkVectorWindowClass",
                                     "ArkVector Window",
                                     WS_OVERLAPPEDWINDOW,
                                     static_cast<i32>(posX),
                                     static_cast<i32>(posY),
                                     static_cast<i32>(m_WindowSize.Width),
                                     static_cast<i32>(m_WindowSize.Height),
                                     nullptr,
                                     nullptr,
                                     m_Instance,
                                     this);
        ::SetWindowLongPtr(m_Handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
        assert(m_Handle != nullptr);
    }

    void Win32AppWindow::Run() {
        ::ShowWindow(m_Handle, SW_SHOW);
        ::UpdateWindow(m_Handle);

        MSG msg = {nullptr};

        while (msg.message != WM_QUIT) {
            if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
        }
    }

    void Win32AppWindow::Shutdown() {
        ::DestroyWindow(m_Handle);
        m_Handle = nullptr;
    }

    LRESULT Win32AppWindow::MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        const LONG_PTR userData = ::GetWindowLongPtr(hwnd, GWLP_USERDATA);
        const auto appWindow    = reinterpret_cast<Win32AppWindow*>(userData);

        if (!appWindow) {
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }

        switch (msg) {
            case WM_DESTROY:
            case WM_CLOSE:
                ::PostQuitMessage(0);
                return 0;
            case WM_SIZE: {
                const UINT width  = LOWORD(lParam);
                const UINT height = HIWORD(lParam);
                // return appWindow->OnResize(width, height);
                return 0;
            }
            case WM_DISPLAYCHANGE: {
                ::InvalidateRect(hwnd, nullptr, FALSE);
                return 0;
            }
            case WM_PAINT: {
                // return appWindow->OnPaint();
                return 0;
            }
                // case WM_KEYDOWN:
                //     return appWindow->OnKeyDown();
                // case WM_KEYUP:
                //     return appWindow->OnKeyUp();
                // case WM_LBUTTONDOWN:
                //     return appWindow->OnLeftMouseButtonDown();
                // case WM_LBUTTONUP:
                //     return appWindow->OnLeftMouseButtonUp();
                // case WM_RBUTTONDOWN:
                //     return appWindow->OnRightMouseButtonDown();
                // case WM_RBUTTONUP:
                //     return appWindow->OnRightMouseButtonUp();
                // case WM_MOUSEMOVE: {
                //     const auto xPos = GET_X_LPARAM(lParam);
                //     const auto yPos = GET_Y_LPARAM(lParam);
                //     return appWindow->OnMouseMove(xPos, yPos);
            // }
            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }
}  // namespace ArkVector