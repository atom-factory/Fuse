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
    std::unique_ptr<IAppWindow> IAppWindow::Create(const Size<u32>& windowSize) {
#if defined(PLATFORM_WINDOWS)
        return std::make_unique<Win32AppWindow>(windowSize);
#elif defined(PLATFORM_LINUX)
        return std::make_unique<X11AppWindow>(windowSize);
#elif defined(PLATFORM_APPLE)
        return nullptr;
#endif

        return nullptr;
    }

}  // namespace ArkVector