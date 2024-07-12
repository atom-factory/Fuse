// Author: Jake Rieger
// Created: 7/10/2024.
//

#include "Platform.h"
#include "Platform/AppWindow.h"
#include "Platform/Win32AppWindow.h"

using namespace ArkVector;

int main() {
    const auto appWindow = IAppWindow::Create({800, 600});
    appWindow->Initialize();
    appWindow->As<Win32AppWindow>()->Run();
    appWindow->Shutdown();

    return 0;
}
