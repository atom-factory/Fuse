// Author: Jake Rieger
// Created: 7/14/2024.
//

#include "Box.h"
#include "Interfaces/Backend.h"
#include "Interfaces/PluginView.h"

namespace ArkVector::Component {
    Box::Box(const Size<u32>& size, const Offset& position, const Color& fillColor)
        : m_Size(size), m_Position(position), m_FillColor(fillColor) {}

    void Box::Draw(IBackend* backend) {
        backend->DrawRect(m_Size, m_Position, m_FillColor);
    }
}  // namespace ArkVector::Component