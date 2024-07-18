// Author: Jake Rieger
// Created: 7/14/2024.
//

#include "CanvasHelloWorld.h"
#include "Components/Box.h"

namespace Fuse {
    IComponent* CanvasHelloWorld::Draw() {
        const auto box = new Component::Box({200, 100},
                                            {50, 50},
                                            Color(0xFF363A55),
                                            Stroke(Color(0xFF1A1C29), 2.f, EStrokeStyle::Solid));

        return box;
    }
}  // namespace Fuse