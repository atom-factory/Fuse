// Author: Jake Rieger
// Created: 7/14/2024.
//

#include "CanvasHelloWorld.h"
#include "Components/Box.h"

namespace Fuse {
    IComponent* CanvasHelloWorld::Draw() {
        const auto box = new Component::Box({500, 200},
                                            {50, 50},
                                            Color(0xFF00CCFF),
                                            Stroke(Color(0xFFFF0000), 4.f, EStrokeStyle::Solid));

        return box;
    }
}  // namespace Fuse