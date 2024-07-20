// Author: Jake Rieger
// Created: 7/14/2024.
//

#pragma once

#include "Color.h"
#include "OldSize.h"
#include "Stroke.h"
#include "Interfaces/Component.h"
#include "Traits.h"
#include "Interfaces/Interactive.h"

using namespace Fuse::Traits;

namespace Fuse::Component {
    class Box final : public IComponent,
                      public TSingleChild,
                      public IInteractive {
    public:
        explicit Box(const Size<u32>& size,
                     const Offset& position,
                     const Color& fillColor,
                     const Stroke& stroke = {},
                     bool rounded         = false);
        void Draw(IBackend* backend) override;

        void OnPressed() override;

    private:
        Size<u32> m_Size;
        Offset m_Position;
        Color m_FillColor;
        Stroke m_Stroke;
        bool m_Rounded;
    };

}  // namespace Fuse::Component
