// Author: Jake Rieger
// Created: 7/12/2024.
//

#include "CanvasHelloWorld.h"

#include <cstdlib>
#include "X11Parent.h"

static Fuse::CanvasHelloWorld* g_Canvas;

int main() {
    X11Parent::CreateParentWindow();

    g_Canvas          = new Fuse::CanvasHelloWorld(&X11Parent::g_Window, X11Parent::g_Display);
    X11Parent::g_View = g_Canvas->GetView()->As<Fuse::X11PluginView>();

    X11Parent::Run();
    X11Parent::DestroyParentWindow();

    return EXIT_SUCCESS;
}