// Author: Jake Rieger
// Created: 7/14/2024.
//

#pragma once

#include "Color.h"
#include "Size.h"
#include "Interfaces/Component.h"
#include "Traits.h"

using namespace ArkVector::Traits;

namespace ArkVector::Component {
    class Box final : public IComponent,
                      public TSingleChild {
    public:
        explicit Box(const Size<u32>& size, const Offset& position, const Color& fillColor);
        void Draw(IBackend* backend) override;

    private:
        Size<u32> m_Size;
        Offset m_Position;
        Color m_FillColor;
    };

}  // namespace ArkVector::Component
