// Author: Jake Rieger
// Created: 7/14/2024.
//

#pragma once

#include "Interfaces/PluginCanvas.h"

namespace ArkVector {

    class CanvasHelloWorld final : public IPluginCanvas {
    public:
        IComponent* Draw() override;
    };

}  // namespace ArkVector
