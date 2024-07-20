// Author: Jake Rieger
// Created: 7/10/2024.
//

#pragma once

#include "Types.h"

namespace Fuse {
    /**
     * @brief Represents a 2D point in Cartesian coordinate space.
     *
     * Functionally equivalent to a 2D vector.
     */
    class Offset {
    public:
        Offset() = default;
        Offset(const f32 x, const f32 y) : X(x), Y(y) {}

        bool operator==(const Offset&) const;
        Offset operator-() const;
        Offset operator+(const Offset&) const;
        Offset operator+(f32 scalar) const;
        Offset operator-(const Offset&) const;
        Offset operator-(f32 scalar) const;
        Offset operator*(const Offset&) const;
        Offset operator*(f32 scalar) const;
        Offset operator/(const Offset&) const;
        Offset operator/(f32 scalar) const;

        static Offset FromDirection(f32 direction, f32 distance);
        static Offset Lerp(const Offset& a, const Offset& b, f64 t);
        static Offset Centroid(const Vector<Offset>& points);

        [[nodiscard]] f64 Direction() const;
        [[nodiscard]] f64 Distance() const;
        [[nodiscard]] f64 DistanceSqr() const;
        [[nodiscard]] bool IsFinite() const;
        [[nodiscard]] bool IsInfinite() const;
        [[nodiscard]] Offset Scale(f32 scaleX, f32 scaleY) const;
        [[nodiscard]] Offset Translate(f32 translateX, f32 translateY) const;

        static Offset Infinite;
        static Offset Zero;

        f32 X = 0;
        f32 Y = 0;
    };
}  // namespace Fuse
