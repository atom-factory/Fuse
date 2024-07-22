// Author: Jake Rieger
// Created: 7/20/2024.
//

#pragma once

#include "OldSize.h"
#include "Types.h"

namespace Fuse {
    // clang-format off
    /**
     * @brief Returns a coordinate value positioned by a percentage of a screen axis.
     *
     * It is functionally equivalent to CSS's `vw` and `vh` units.
     *
     * @warning Percent values are specified in range [0, 100], NOT [0.0, 1.0]
     *
     * @code{.cpp}
     * auto dim = Dimension(viewSize);
     * // 20% of the screen width
     * auto boxWidth = dim.Height(20.f);
     * // Position the box 90% across the screen from the left side (10% from the right).
     * auto boxPosX = dim.WidthRight(10.f);
     * @endcode
     */
    // clang-format on
    class Dimension {
    public:
        explicit Dimension(const Size<u32>& viewSize) : m_Size(viewSize) {}

        f32 Width(const f32 value) const {
            return (value / 100.f) * m_Size.Width;
        }

        f32 Height(const f32 value) const {
            return (value / 100.f) * m_Size.Height;
        }

        f32 WidthRight(const f32 value) const {
            const auto width = Width(value);
            return m_Size.Width - width;
        }

        f32 HeightBottom(const f32 value) const {
            const auto height = Height(value);
            return m_Size.Height - height;
        }

    private:
        Size<u32> m_Size;
    };
}  // namespace Fuse