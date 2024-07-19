// Author: Jake Rieger
// Created: 7/14/2024.
//

#include "Box.h"
#include "Interfaces/Backend.h"
#include "Interfaces/PluginView.h"

namespace Fuse::Component {
    Box::Box(const Size<u32>& size,
             const Offset& position,
             const Color& fillColor,
             const Stroke& stroke,
             const bool rounded)
        : m_Size(size), m_Position(position), m_FillColor(fillColor), m_Stroke(stroke),
          m_Rounded(rounded) {}

    void Box::Draw(IBackend* backend) {
        backend->DrawRect(m_Size, m_Position, m_FillColor, m_Stroke, m_Rounded);
    }
    void Box::OnPressed() {
#if defined(PLATFORM_WINDOWS)
        printf("OnPressed() called for this component.\n");
#endif
    }
}  // namespace Fuse::Component