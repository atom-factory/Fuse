// Author: Jake Rieger
// Created: 7/14/2024.
//

#include "CanvasHelloWorld.h"

#include "CustomComponent.h"
#include "Components/Box.h"
#include "Components/RotaryKnob.h"

namespace Fuse {
    IComponent* CanvasHelloWorld::Draw(IPluginView* viewContext) {
        const auto viewSize = viewContext->GetSize();
        const auto root     = new Component::Box(viewSize,
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

        const auto topCutout =
          new CustomComponent(Offset::Zero,
                              {
                                {viewSize.Width * 0.3f, 0},
                                {viewSize.Width * 0.7f, 0},
                                {viewSize.Width * 0.60f, viewSize.Height * 0.18f},
                                {viewSize.Width * 0.40f, viewSize.Height * 0.18f},
                              },
                              Color(0x0a0b10),
                              {});

        const auto bottomCutout = new CustomComponent(Offset::Zero,
                                                      {
                                                        {},
                                                        {},
                                                        {},
                                                        {},
                                                      },
                                                      Colors::Black,
                                                      {});

        // root->AddChild(knobGain);
        // root->AddChild(knobBalance);
        root->AddChild(topCutout);
        root->AddChild(bottomCutout);

        return root;
    }
}  // namespace Fuse