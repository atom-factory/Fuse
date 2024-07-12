// Author: Jake Rieger
// Created: 7/12/2024.
//

#include "AppWindow.h"

#if defined(PLATFORM_WINDOWS)
    #include "Win32AppWindow.h"
#elif defined(PLATFORM_LINUX)
    #include "X11AppWindow.h"
#elif defined(PLATFORM_APPLE)
    #include "NSAppWindow.h"
#endif

namespace ArkVector {
    IAppWindow* IAppWindow::Create(const Size<u32>& windowSize) {
#if defined(PLATFORM_WINDOWS)
        return new Win32AppWindow(windowSize);
#elif defined(PLATFORM_LINUX)
        return new X11AppWindow(windowSize);
#elif defined(PLATFORM_APPLE)
        return nullptr;
#endif

        return nullptr;
    }

}  // namespace ArkVector