// Author: Jake Rieger
// Created: 7/16/24.
//

#pragma once

#include <iostream>

#include "Types.h"
#include "Platform/Platform.h"
#include "Platform/WaylandPluginView.h"

namespace WaylandParent {
    static inline ArkVector::WaylandPluginView* g_View;

    static int CreateParentWindow() {
        return 0;
    }

    static void Run() {}

    static void DestroyParentWindow() {}
}