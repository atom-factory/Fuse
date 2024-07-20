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

    class BackgroundCutout final : public IComponent,
                                   public TSingleChild {
    public:
        explicit BackgroundCutout(const Offset& position,
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
