// Author: Jake Rieger
// Created: 7/14/2024.
//

#pragma once

#include "Interfaces/PluginCanvas.h"

namespace ArkVector {

    class CanvasHelloWorld final : public IPluginCanvas {
    public:
        explicit CanvasHelloWorld(const Size<u32>& size, void* parent)
            : IPluginCanvas(size, parent) {
            this->IPluginCanvas::AttachToParent(parent);
        }
        IComponent* Draw() override;
    };

}  // namespace ArkVector
