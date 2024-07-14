// Author: Jake Rieger
// Created: 7/10/2024.
//

#include "Platform/Platform.h"
#include "CanvasHelloWorld.h"
#include "HWNDParent.h"

using namespace ArkVector;

static constexpr int WINDOW_WIDTH  = 800;
static constexpr int WINDOW_HEIGHT = 600;

static CanvasHelloWorld* g_Canvas;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    HWNDParent::CreateParentWindow(hInstance, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Create our canvas
    g_Canvas = new CanvasHelloWorld;
    // Attach our canvas to our parent window
    g_Canvas->AttachToParent(HWNDParent::g_Window);

    HWNDParent::Run();

    return 0;
}