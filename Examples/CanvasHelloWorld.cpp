// Author: Jake Rieger
// Created: 7/14/2024.
//

#include "CanvasHelloWorld.h"
#include "Box.h"

namespace ArkVector {
    IComponent* CanvasHelloWorld::Draw() {
        return new Component::Box;
    }
}  // namespace ArkVector