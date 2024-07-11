// Author: Jake Rieger
// Created: 7/10/2024.
//

#include "Platform/Win32AppWindow.h"

int main() {
    ArkVector::IAppWindow* appWindow = nullptr;

#if defined(PLATFORM_WINDOWS)
    appWindow = new ArkVector::Win32AppWindow({800, 600});
#elif defined(PLATFORM_LINUX)
    appWindow = nullptr;
#elif defined(PLATFORM_APPLE)
    appWindow = nullptr;
#endif

    appWindow->Initialize();
    appWindow->Run();
    appWindow->Shutdown();
    delete appWindow;

    return 0;
}