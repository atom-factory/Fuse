// Author: Jake Rieger
// Created: 7/15/2024.
//

#pragma once

#include "Interfaces/Component.h"
#include "Offset.h"
#include "Color.h"
#include "Stroke.h"

namespace Fuse {
    using namespace Traits;

    class CustomComponent final : public IComponent,
                                  public TSingleChild {
    public:
        explicit CustomComponent(const Offset& position,
                                 const Vector<Offset>& points,
                                 const Color& fillColor,
                                 const Stroke& stroke);
        void Draw(IBackend* backend) override;

    private:
        Offset m_Position;
        Vector<Offset> m_Points;
        Color m_FillColor;
        Stroke m_Stroke;
    };
}  // namespace Fuse
