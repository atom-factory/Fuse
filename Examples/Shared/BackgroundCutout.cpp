// Author: Jake Rieger
// Created: 7/15/2024.
//

#include "BackgroundCutout.h"
#include "Components/Text.h"
#include "Interfaces/Backend.h"

namespace Fuse {
    BackgroundCutout::BackgroundCutout(const Offset& position,
                                       const Vector<Offset>& points,
                                       const Color& fillColor,
                                       const Stroke& stroke)
        : m_Position(position), m_Points(points), m_FillColor(fillColor), m_Stroke(stroke) {
        if (points.size() < 3) {
            throw std::invalid_argument("BackgroundCutout::BackgroundCutout: Too few points.");
        }
    }

    void BackgroundCutout::Draw(IBackend* backend) {
        backend->DrawPath(m_Position, m_Points, m_FillColor, m_Stroke);
    }
}  // namespace Fuse