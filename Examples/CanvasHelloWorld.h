// Author: Jake Rieger
// Created: 7/14/2024.
//

#pragma once

#include "Interfaces/PluginCanvas.h"

namespace Fuse {

    class CanvasHelloWorld final : public IPluginCanvas {
    public:
        explicit CanvasHelloWorld(void* parent) : IPluginCanvas(parent) {
            this->BackgroundColor = Color(0xFF11121B);
            this->IPluginCanvas::AttachToParent(parent);
        }

#ifdef USE_X11
        explicit CanvasHelloWorld(void* parent, Display* display) : IPluginCanvas(parent) {
            this->BackgroundColor = Color(0xFF01030C);
            this->GetView()->As<X11PluginView>()->SetDisplay(display);
            this->IPluginCanvas::AttachToParent(parent);
        }
#endif

        IComponent* Draw() override;
    };

}  // namespace Fuse
