// Author: Jake Rieger
// Created: 7/14/2024.
//

#include "CanvasHelloWorld.h"
#include "Components/Box.h"

namespace Fuse {
    IComponent* CanvasHelloWorld::Draw(IPluginView* viewContext) {
        auto viewSize    = viewContext->GetSize();
        const auto bgBox = new Component::Box(viewSize,
                                              Offset::Zero,
                                              Color(0x1a1c29),
                                              Stroke(Color(0x0a0b10), 16.f, EStrokeStyle::Solid));

        return bgBox;
    }
}  // namespace Fuse