// Author: Jake Rieger
// Created: 7/17/2024.
//

#include "RotaryKnob.h"

#include "Interfaces/Backend.h"

namespace Fuse::Component {
    RotaryKnob::RotaryKnob(const f32 radius,
                           const Offset& position,
                           const Color& fillColor,
                           const Stroke& stroke)
        : IComponent(Rectangle::FromCircle(position, radius)), m_Radius(radius),
          m_Position(position), m_FillColor(fillColor), m_Stroke(stroke) {}

    void RotaryKnob::Draw(IBackend* backend) {
        backend->DrawEllipse(m_Radius, m_Position, m_FillColor, m_Stroke);
        backend->DrawBoundingBox(m_Rect);
    }

    void RotaryKnob::OnPressed() {
        IInteractive::OnPressed();
    }
}  // namespace Fuse::Component