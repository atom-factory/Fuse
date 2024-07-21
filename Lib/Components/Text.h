// Author: Jake Rieger
// Created: 7/21/2024.
//

#pragma once

#include "Color.h"
#include "Offset.h"
#include "Interfaces/Component.h"
#include "Traits.h"
#include "Types.h"

namespace Fuse::Component {
    class Text final : public IComponent {
    public:
        explicit Text(const str& value, const Offset& position, f32 size, const Color& color);
        void Draw(IBackend* backend) override;

    private:
        str m_Value;
        Offset m_Position;
        f32 m_Size;
        Color m_FillColor;
    };
}  // namespace Fuse::Component