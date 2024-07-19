// Author: Jake Rieger
// Created: 7/14/2024.
//

#include "CanvasHelloWorld.h"
#include "Components/Box.h"
#include "Components/RotaryKnob.h"

namespace Fuse {
    IComponent* CanvasHelloWorld::Draw(IPluginView* viewContext) {
        const auto viewSize = viewContext->GetSize();
        const auto bgBox    = new Component::Box(viewSize,
                                              Offset::Zero,
                                              Color(0x1a1c29),
                                              Stroke(Color(0x0a0b10), 16.f, EStrokeStyle::Solid));

        const auto knobGain =
          new Component::RotaryKnob(80.f,
                                    {120, 140},
                                    Color(0x363a55),
                                    Stroke(Color(0x11121b), 8.f, EStrokeStyle::Solid));
        const auto knobBalance =
          new Component::RotaryKnob(80.f,
                                    {static_cast<float>(viewSize.Width - 120), 140},
                                    Color(0x363a55),
                                    Stroke(Color(0x11121b), 8.f, EStrokeStyle::Solid));
        bgBox->AddChild(knobGain);
        bgBox->AddChild(knobBalance);

        return bgBox;
    }
}  // namespace Fuse