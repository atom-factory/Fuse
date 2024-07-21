// Author: Jake Rieger
// Created: 7/12/2024.
//

#pragma once

#include "Types.h"
#include "Platform/Platform.h"
#include "Platform/Win32PluginView.h"
#include "../Examples/Res/resource.h"

#include <iostream>

namespace HWNDParent {
    static inline HINSTANCE g_Instance;
    static inline HWND g_Window;
    static inline Fuse::Win32PluginView* g_View;
    inline i32 g_InitialWidth, g_InitialHeight;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    static int CreateParentWindow(HINSTANCE instance, const i32 width, const i32 height) {
        g_InitialWidth      = width;
        g_InitialHeight     = height;
        g_Instance          = instance;
        const HICON appIcon = ::LoadIcon(g_Instance, MAKEINTRESOURCE(APPICON));

        WNDCLASSEXA wndClass   = {};
        wndClass.cbSize        = sizeof(WNDCLASSEXA);
        wndClass.style         = CS_HREDRAW | CS_VREDRAW;
        wndClass.lpfnWndProc   = WindowProc;
        wndClass.cbClsExtra    = 0;
        wndClass.cbWndExtra    = 0;
        wndClass.hInstance     = g_Instance;
        wndClass.hIcon         = appIcon;
        wndClass.hIconSm       = wndClass.hIcon;
        wndClass.hCursor       = ::LoadCursor(nullptr, IDC_ARROW);
        wndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        wndClass.lpszMenuName  = nullptr;
        wndClass.lpszClassName = "FuseParentWindowClass";

        RegisterClassExA(&wndClass);

        const u32 scrWidth  = ::GetSystemMetrics(SM_CXSCREEN);
        const u32 scrHeight = ::GetSystemMetrics(SM_CYSCREEN);
        const u32 posX      = (scrWidth - width) / 2;
        const u32 posY      = (scrHeight - height) / 2;

        g_Window = ::CreateWindowExA(NULL,
                                     "FuseParentWindowClass",
                                     "Win32 Window - Fuse",
                                     WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
                                     static_cast<i32>(posX),
                                     static_cast<i32>(posY),
                                     width,
                                     height,
                                     nullptr,
                                     nullptr,
                                     g_Instance,
                                     nullptr);

        if (!g_Window) {
            return -1;
        }

        ::ShowWindow(g_Window, SW_SHOW);
        ::UpdateWindow(g_Window);

        return 0;
    }

    static void Run() {
        MSG msg = {};
        while (msg.message != WM_QUIT) {
            if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
        }
    }

    static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        switch (msg) {
            case WM_SIZE: {
                if (g_View != nullptr) {
                    RECT rect;
                    GetClientRect(hwnd, &rect);
                    auto width  = static_cast<u32>(rect.right - rect.left);
                    auto height = static_cast<u32>(rect.bottom - rect.top);
                    g_View->OnResize({width, height});
                }
            }
            case WM_KEYDOWN: {
                auto keyCode = static_cast<u32>(wParam);

                RECT position;
                ::GetWindowRect(g_Window, &position);

                switch (keyCode) {
                    case VK_NUMPAD1:
                        ::SetWindowPos(g_Window,
                                       nullptr,
                                       position.left,
                                       position.top,
                                       g_InitialWidth,
                                       g_InitialHeight,
                                       SWP_NOZORDER | SWP_NOACTIVATE);
                        break;
                    case VK_NUMPAD2:
                        ::SetWindowPos(g_Window,
                                       nullptr,
                                       position.left,
                                       position.top,
                                       g_InitialWidth * 1.25,
                                       g_InitialHeight * 1.25,
                                       SWP_NOZORDER | SWP_NOACTIVATE);
                        break;
                    case VK_NUMPAD3:
                        ::SetWindowPos(g_Window,
                                       nullptr,
                                       position.left,
                                       position.top,
                                       g_InitialWidth * 1.5,
                                       g_InitialHeight * 1.5,
                                       SWP_NOZORDER | SWP_NOACTIVATE);
                        break;
                    default:
                        break;
                }
            }
                return 0;
            case WM_DESTROY:
                g_View->Shutdown();
                ::DestroyWindow(hwnd);
                ::PostQuitMessage(0);
                return 0;
            default:
                return ::DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }
}  // namespace HWNDParent