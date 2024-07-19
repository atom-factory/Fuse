// Author: Jake Rieger
// Created: 7/10/2024.
//

#include "Platform/Platform.h"
#include "CanvasHelloWorld.h"
#include "HWNDParent.h"

using namespace Fuse;

static constexpr int WINDOW_WIDTH  = 800;
static constexpr int WINDOW_HEIGHT = 600;

static CanvasHelloWorld* g_Canvas;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    HWNDParent::CreateParentWindow(hInstance, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Create our canvas
    g_Canvas           = new CanvasHelloWorld(HWNDParent::g_Window);
    HWNDParent::g_View = g_Canvas->GetView()->As<Win32PluginView>();

    HWNDParent::Run();

    delete g_Canvas;
    return 0;
}