// Author: Jake Rieger
// Created: 7/19/2024.
//

#pragma once

#include "Types.h"
#include "Offset.h"
#include "OldSize.h"

namespace Fuse {
    class Rectangle {
    public:
        Rectangle() = default;
        Rectangle(const Offset& offset, const Size<f32>& size);
        Rectangle(f32 left, f32 top, f32 right, f32 bottom);

        static Rectangle FromCenter(const Offset& center, f32 width, f32 height);
        static Rectangle FromCircle(const Offset& center, f32 radius);
        static Rectangle FromLTWH(f32 left, f32 top, f32 width, f32 height);
        static Rectangle FromPoints(const Offset& a, const Offset& b);
        static Rectangle Copy(const Rectangle& other);

        [[nodiscard]] f32 Height() const;
        [[nodiscard]] f32 Width() const;
        [[nodiscard]] f32 Top() const;
        [[nodiscard]] f32 Left() const;
        [[nodiscard]] f32 Bottom() const;
        [[nodiscard]] f32 Right() const;
        [[nodiscard]] f32 LongestSide() const;
        [[nodiscard]] f32 ShortestSide() const;

        [[nodiscard]] Offset BottomCenter() const;
        [[nodiscard]] Offset BottomLeft() const;
        [[nodiscard]] Offset BottomRight() const;
        [[nodiscard]] Offset Center() const;
        [[nodiscard]] Offset CenterLeft() const;
        [[nodiscard]] Offset CenterRight() const;
        [[nodiscard]] Offset TopCenter() const;
        [[nodiscard]] Offset TopLeft() const;
        [[nodiscard]] Offset TopRight() const;

        [[nodiscard]] bool Contains(const Offset& offset) const;
        [[nodiscard]] bool Overlaps(const Rectangle& other) const;

        [[nodiscard]] Rectangle Shrink(f32 delta) const;
        [[nodiscard]] Rectangle BoundingBox(const Rectangle& other) const;
        [[nodiscard]] Rectangle Grow(f32 delta) const;
        [[nodiscard]] Rectangle Intersect(const Rectangle& other) const;
        [[nodiscard]] Rectangle Shift(const Offset& offset) const;
        [[nodiscard]] Rectangle Translate(f32 translateX, f32 translateY) const;

        static Rectangle Largest;
        static Rectangle Zero;
        static Rectangle Lerp(const Rectangle& a, const Rectangle& b, f32 t);

    private:
        f32 m_Left;
        f32 m_Top;
        f32 m_Right;
        f32 m_Bottom;
    };
}  // namespace Fuse