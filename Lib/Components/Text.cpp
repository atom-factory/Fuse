// Author: Jake Rieger
// Created: 7/21/2024.
//

#include "Text.h"
#include "Interfaces/Backend.h"

namespace Fuse::Component {
    Text::Text(const str& value, const Offset& position, const f32 size, const Color& color)
        : m_Value(value), m_Position(position), m_Size(size), m_FillColor(color) {}

    void Text::Draw(IBackend* backend) {
        backend->DrawString(m_Value, m_Position, m_Size, m_FillColor);
    }

}  // namespace Fuse::Component