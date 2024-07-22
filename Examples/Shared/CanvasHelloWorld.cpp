// Author: Jake Rieger
// Created: 7/14/2024.
//

#include "CanvasHelloWorld.h"

#include "BackgroundCutout.h"
#include "Components/Box.h"
#include "Components/RotaryKnob.h"
#include "Components/Text.h"

namespace Fuse {
    IComponent* CanvasHelloWorld::Draw(IPluginView* viewContext, const Dimension dim) {
        // This is a rough idea of how one might lay out a simple UI. The `viewSize` stuff will
        // preferably get replaced with positioning and alignment components.
        const auto viewSize = viewContext->GetSize();
        const auto viewRect = viewContext->GetViewRect();

        const auto root =
          new Component::Box(viewSize,
                             Offset::Zero,
                             Color(0x1a1c29),
                             Stroke(Color(0x0a0b10), dim.Width(3.f), EStrokeStyle::Solid));

        const auto knobGain =
          new Component::RotaryKnob(dim.Height(30.f),
                                    {dim.Width(21.f), dim.Height(54.f)},
                                    Color(0x363a55),
                                    Stroke(Color(0x11121b), dim.Width(1.5f), EStrokeStyle::Solid));
        const auto knobBalance =
          new Component::RotaryKnob(dim.Height(30.f),
                                    {dim.Width(79.f), dim.Height(54.f)},
                                    Color(0x363a55),
                                    Stroke(Color(0x11121b), dim.Width(1.5f), EStrokeStyle::Solid));

        const auto topCutout = new BackgroundCutout(Offset::Zero,
                                                    {
                                                      {dim.Width(30.f), 0},
                                                      {dim.Width(70.f), 0},
                                                      {dim.Width(60.f), dim.Height(18.f)},
                                                      {dim.Width(40.f), dim.Height(18.f)},
                                                    },
                                                    Color(0x0a0b10),
                                                    {});

        const auto bottomCutout = new BackgroundCutout(Offset::Zero,
                                                       {
                                                         {dim.Width(30.f), dim.Height(100.f)},
                                                         {dim.Width(70.f), dim.Height(100.f)},
                                                         {dim.Width(60.f), dim.HeightBottom(18.f)},
                                                         {dim.Width(40.f), dim.HeightBottom(18.f)},
                                                       },
                                                       Color(0x0a0b10),
                                                       {});

        const auto centerCutout = new BackgroundCutout(
          Offset::Zero,
          {
            {viewRect.Center().X - dim.Width(1.4f), dim.Height(18.f)},
            {viewRect.Center().X + dim.Width(1.4f), dim.Height(18.f)},
            {viewRect.Center().X + dim.Width(1.4f), viewRect.Bottom() - dim.Height(18.f)},
            {viewRect.Center().X - dim.Width(1.4f), viewRect.Bottom() - dim.Height(18.f)},
          },
          Color(0x0a0b10),
          {});

        const auto pluginName = new Component::Text("ARKGain",
                                                    {
                                                      dim.Width(100.f),
                                                      dim.Height(18.f),
                                                    },
                                                    16.f,
                                                    Color(0x22AACC));
        topCutout->AddChild(pluginName);

        root->AddChild(knobGain);
        root->AddChild(knobBalance);
        root->AddChild(topCutout);
        root->AddChild(bottomCutout);
        root->AddChild(centerCutout);

        return root;
    }
}  // namespace Fuse