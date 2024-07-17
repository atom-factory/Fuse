// Author: Jake Rieger
// Created: 7/17/2024.
//

#pragma once

#include "Types.h"
#include "Color.h"

namespace Fuse {
    enum class EStrokeStyle {
        Solid,
        Dashed,
        Dotted,
        Double,
    };

    struct Stroke {
        Stroke() = default;
        Stroke(const Color& color, const f32 thickness, const EStrokeStyle style)
            : Color(color), Thickness(thickness), Style(style) {}
        Color Color        = Colors::Transparent;
        f32 Thickness      = 0.f;
        EStrokeStyle Style = EStrokeStyle::Solid;
    };
}  // namespace Fuse