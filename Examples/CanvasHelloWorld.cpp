// Author: Jake Rieger
// Created: 7/14/2024.
//

#include "CanvasHelloWorld.h"
#include "Components/Box.h"

namespace Fuse {
    IComponent* CanvasHelloWorld::Draw() {
        return new Component::Box({500, 200}, {50, 50}, Color(0xFF00CCFF));
    }
}  // namespace Fuse