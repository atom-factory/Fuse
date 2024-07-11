// Author: Jake Rieger
// Created: 7/10/2024.
//

#include "Platform.h"
#include "Platform/AppWindow.h"

#if defined(PLATFORM_WINDOWS)
    #include "Platform/Win32AppWindow.h"
#elif defined(PLATFORM_LINUX)
    #include "Platform/X11AppWindow.h"
#elif defined(PLATFORM_APPLE)
#endif

int main() {
    ArkVector::IAppWindow* appWindow = nullptr;

#if defined(PLATFORM_WINDOWS)
    appWindow = new ArkVector::Win32AppWindow({800, 600});
#elif defined(PLATFORM_LINUX)
    appWindow = new ArkVector::X11AppWindow({800, 600});
#elif defined(PLATFORM_APPLE)
    appWindow = nullptr;
#endif

    appWindow->Initialize(nullptr);
    appWindow->Run();
    appWindow->Shutdown();
    delete appWindow;

    return 0;
}