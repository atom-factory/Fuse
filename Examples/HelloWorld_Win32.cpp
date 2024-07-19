// Author: Jake Rieger
// Created: 7/10/2024.
//

#include "Platform/Platform.h"
#include "CanvasHelloWorld.h"
#include "HWNDParent.h"

using namespace Fuse;

static constexpr int kWindowWidth  = 600;
static constexpr int kWindowHeight = 300;

static CanvasHelloWorld* g_Canvas;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    HWNDParent::CreateParentWindow(hInstance, kWindowWidth, kWindowHeight);

    // Create our canvas
    g_Canvas           = new CanvasHelloWorld(HWNDParent::g_Window);
    HWNDParent::g_View = g_Canvas->GetView()->As<Win32PluginView>();

    HWNDParent::Run();

    delete g_Canvas;
    return 0;
}