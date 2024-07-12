// Author: Jake Rieger
// Created: 7/12/2024.
//

#pragma once

#include "Types.h"
#include "Platform/Platform.h"
#include "Platform/Win32PluginView.h"

namespace HWNDParent {
    static inline HINSTANCE g_Instance;
    static inline HWND g_Window;
    static inline ArkVector::Win32PluginView* g_View;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    static int CreateParentWindow(HINSTANCE instance, const i32 width, const i32 height) {
        g_Instance = instance;

        WNDCLASSEXA wndClass   = {};
        wndClass.cbSize        = sizeof(WNDCLASSEXA);
        wndClass.style         = CS_HREDRAW | CS_VREDRAW;
        wndClass.lpfnWndProc   = WindowProc;
        wndClass.cbClsExtra    = 0;
        wndClass.cbWndExtra    = 0;
        wndClass.hInstance     = g_Instance;
        wndClass.hIcon         = ::LoadIcon(nullptr, IDI_APPLICATION);
        wndClass.hIconSm       = wndClass.hIcon;
        wndClass.hCursor       = ::LoadCursor(nullptr, IDC_ARROW);
        wndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        wndClass.lpszMenuName  = nullptr;
        wndClass.lpszClassName = "ArkVectorParentWindowClass";

        RegisterClassExA(&wndClass);

        const u32 scrWidth  = ::GetSystemMetrics(SM_CXSCREEN);
        const u32 scrHeight = ::GetSystemMetrics(SM_CYSCREEN);
        const u32 posX      = (scrWidth - width) / 2;
        const u32 posY      = (scrHeight - height) / 2;

        g_Window = ::CreateWindowExA(NULL,
                                     "ArkVectorParentWindowClass",
                                     "ArkVector Window",
                                     WS_OVERLAPPEDWINDOW | WS_VISIBLE,
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
        PAINTSTRUCT ps;
        HDC hdc;
        switch (msg) {
            case WM_PAINT: {
                hdc = BeginPaint(hwnd, &ps);

                // Set the background color to blue
                HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
                FillRect(hdc, &ps.rcPaint, hBrush);

                DeleteObject(hBrush);
                EndPaint(hwnd, &ps);
                return 0;
            }
            case WM_SIZE: {
                if (g_View != nullptr) {
                    RECT rect;
                    GetClientRect(hwnd, &rect);
                    auto width  = static_cast<u32>(rect.right - rect.left);
                    auto height = static_cast<u32>(rect.bottom - rect.top);
                    g_View->OnResize({width, height});
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