// Author: Jake Rieger
// Created: 7/17/2024.
//

#pragma once

#include "Offset.h"
#include "Color.h"
#include "Stroke.h"
#include "Interfaces/Component.h"
#include "Traits.h"
#include "Interfaces/Interactive.h"

using namespace Fuse::Traits;

namespace Fuse::Component {
    class RotaryKnob final : public IComponent,
                             public TSingleChild,
                             public IInteractive {
    public:
        explicit RotaryKnob(f32 radius,
                            const Offset& position,
                            const Color& fillColor,
                            const Stroke& stroke);
        void Draw(IBackend* backend) override;
        void OnPressed() override;

    private:
        f32 m_Radius;
        Offset m_Position;
        Color m_FillColor;
        Stroke m_Stroke;
    };
}  // namespace Fuse::Component