// Author: Jake Rieger
// Created: 7/14/2024.
//

#include "CanvasHelloWorld.h"

#include "BackgroundCutout.h"
#include "Components/Box.h"
#include "Components/RotaryKnob.h"

namespace Fuse {
    IComponent* CanvasHelloWorld::Draw(IPluginView* viewContext) {
        // This is a rough idea of how one might lay out a simple UI. The `viewSize` stuff will
        // preferably get replaced with positioning and alignment components.
        const auto viewSize = viewContext->GetSize();
        const auto root =
          new Component::Box(viewSize,
                             Offset::Zero,
                             Color(0x1a1c29),
                             Stroke(Color(0x0a0b10), viewSize.Width * 0.03f, EStrokeStyle::Solid));

        const auto knobGain =
          new Component::RotaryKnob(viewSize.Height * 0.3f,
                                    {120, 140},
                                    Color(0x363a55),
                                    Stroke(Color(0x11121b), 8.f, EStrokeStyle::Solid));
        const auto knobBalance =
          new Component::RotaryKnob(viewSize.Height * 0.3f,
                                    {static_cast<float>(viewSize.Width - 120), 140},
                                    Color(0x363a55),
                                    Stroke(Color(0x11121b), 8.f, EStrokeStyle::Solid));

        const auto topCutout =
          new BackgroundCutout(Offset::Zero,
                               {
                                 {viewSize.Width * 0.3f, 0},
                                 {viewSize.Width * 0.7f, 0},
                                 {viewSize.Width * 0.60f, viewSize.Height * 0.18f},
                                 {viewSize.Width * 0.40f, viewSize.Height * 0.18f},
                               },
                               Color(0x0a0b10),
                               {});

        const auto bottomCutout = new BackgroundCutout(
          Offset::Zero,
          {
            {viewSize.Width * 0.3f, viewSize.Height * 1.f},
            {viewSize.Width * 0.7f, viewSize.Height * 1.f},
            {viewSize.Width * 0.60f, viewSize.Height - (viewSize.Height * 0.18f)},
            {viewSize.Width * 0.40f, viewSize.Height - (viewSize.Height * 0.18f)},
          },
          Color(0x0a0b10),
          {});

        const auto centerCutout = new BackgroundCutout(
          Offset::Zero,
          {
            {viewSize.Width / 2.f - 8.f, viewSize.Height * 0.18f},
            {viewSize.Width / 2.f + 8.f, viewSize.Height * 0.18f},
            {viewSize.Width / 2.f + 8.f, viewSize.Height - (viewSize.Height * 0.18f)},
            {viewSize.Width / 2.f - 8.f, viewSize.Height - (viewSize.Height * 0.18f)},
          },
          Color(0x0a0b10),
          {});

        // Add everything as a child to our root since this example doesn't take advantage of nested
        // components.
        root->AddChild(knobGain);
        root->AddChild(knobBalance);
        root->AddChild(topCutout);
        root->AddChild(bottomCutout);
        root->AddChild(centerCutout);

        return root;
    }
}  // namespace Fuse