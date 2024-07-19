// Author: Jake Rieger
// Created: 7/16/24.
//

#pragma once

#include "Types.h"
#include "Platform/Platform.h"
#include "Platform/WaylandPluginView.h"

namespace WaylandParent {
    static inline Fuse::WaylandPluginView* g_View;

    static wl_display* g_Display       = nullptr;
    static wl_compositor* g_Compositor = nullptr;
    static wl_surface* g_Surface       = nullptr;
    static wl_subsurface* g_Subsurface = nullptr;
    static wl_egl_window* g_EglWindow  = nullptr;
    static xdg_wm_base* g_XdgWmBase    = nullptr;

    static int CreateParentWindow() {
        return 0;
    }

    static void Run() {}

    static void DestroyParentWindow() {}
}