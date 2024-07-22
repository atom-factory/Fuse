// Author: Jake Rieger
// Created: 7/20/2024.
//

#pragma once

#include "OldSize.h"
#include "Types.h"

namespace Fuse {
    /**
     * @brief A template class for size and position dimensions
     *
     * @todo Actually implement this across the rest of the library classes.
     */
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