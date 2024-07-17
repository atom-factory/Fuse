// Author: Jake Rieger
// Created: 7/14/2024.
//

#pragma once

#include "Interfaces/PluginCanvas.h"

namespace Fuse {

    class CanvasHelloWorld final : public IPluginCanvas {
    public:
        explicit CanvasHelloWorld(void* parent) : IPluginCanvas(parent) {
            this->BackgroundColor = Color(0xFF01030C);
            this->IPluginCanvas::AttachToParent(parent);
        }
        IComponent* Draw() override;
    };

}  // namespace Fuse
