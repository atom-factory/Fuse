// Author: Jake Rieger
// Created: 7/10/2024.
//

#include "Platform/Platform.h"
#include "Platform/Win32PluginView.h"
#include "HWNDParent.h"

using namespace ArkVector;

static constexpr int WINDOW_WIDTH  = 800;
static constexpr int WINDOW_HEIGHT = 600;

Win32PluginView* g_View;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    HWNDParent::CreateParentWindow(hInstance, WINDOW_WIDTH, WINDOW_HEIGHT);

    const auto view = IPluginView::Create({WINDOW_WIDTH, WINDOW_HEIGHT});
    g_View          = view->As<Win32PluginView>();
    g_View->Initialize(HWNDParent::g_Window, SW_SHOW);

    HWNDParent::g_View = g_View;
    HWNDParent::Run();

    return 0;
}