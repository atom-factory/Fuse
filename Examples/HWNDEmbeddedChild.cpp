// Author: Jake Rieger
// Created: 7/10/2024.
//

#include "Platform.h"
#include "Platform/AppWindow.h"
#include "Platform/Win32AppWindow.h"

using namespace ArkVector;

static constexpr int WINDOW_WIDTH  = 800;
static constexpr int WINDOW_HEIGHT = 600;

HINSTANCE g_hInstance;
HWND g_hwnd;
Win32AppWindow* g_appWindow;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void Attached();
void Removed();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    g_hInstance = hInstance;

    WNDCLASSEXA wndClass   = {};
    wndClass.cbSize        = sizeof(WNDCLASSEXA);
    wndClass.style         = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc   = WndProc;
    wndClass.cbClsExtra    = 0;
    wndClass.cbWndExtra    = 0;
    wndClass.hInstance     = g_hInstance;
    wndClass.hIcon         = ::LoadIcon(nullptr, IDI_APPLICATION);
    wndClass.hIconSm       = wndClass.hIcon;
    wndClass.hCursor       = ::LoadCursor(nullptr, IDC_ARROW);
    wndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wndClass.lpszMenuName  = nullptr;
    wndClass.lpszClassName = "ArkVectorWindowClass";

    RegisterClassExA(&wndClass);

    const u32 scrWidth  = ::GetSystemMetrics(SM_CXSCREEN);
    const u32 scrHeight = ::GetSystemMetrics(SM_CYSCREEN);
    const u32 posX      = (scrWidth - WINDOW_WIDTH) / 2;
    const u32 posY      = (scrHeight - WINDOW_HEIGHT) / 2;

    g_hwnd = ::CreateWindowExA(NULL,
                               "ArkVectorWindowClass",
                               "ArkVector Window",
                               WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                               static_cast<i32>(posX),
                               static_cast<i32>(posY),
                               WINDOW_WIDTH,
                               WINDOW_HEIGHT,
                               nullptr,
                               nullptr,
                               g_hInstance,
                               nullptr);

    if (!g_hwnd) {
        return -1;
    }

    Attached();

    ::ShowWindow(g_hwnd, nCmdShow);
    ::UpdateWindow(g_hwnd);

    MSG msg = {};
    while (msg.message != WM_QUIT) {
        if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
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
        case WM_DESTROY:
            Removed();
            ::DestroyWindow(hwnd);
            ::PostQuitMessage(0);
            return 0;
        default:
            return ::DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

void Attached() {
    g_appWindow = IAppWindow::Create({WINDOW_WIDTH, WINDOW_HEIGHT})->As<Win32AppWindow>();
    g_appWindow->Initialize(g_hwnd);
}

void Removed() {
    g_appWindow->Shutdown();
}