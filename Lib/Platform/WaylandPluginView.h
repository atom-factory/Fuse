// Author: Jake Rieger
// Created: 7/15/2024.
//

#pragma once

#include "Platform.h"
#include "Interfaces/PluginView.h"

namespace Fuse {
    class WaylandPluginView final : public IPluginView {
    public:
        explicit WaylandPluginView(wl_display* parent) : IPluginView(parent) {}
        void Shutdown() override;
    };
} // Fuse
