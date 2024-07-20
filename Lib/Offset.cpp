// Author: Jake Rieger
// Created: 7/10/2024.
//

#include "Offset.h"
#include "Maths.h"

#include <cmath>

namespace Fuse {
    Offset Offset::Infinite = {Infinity<f32>(), Infinity<f32>()};
    Offset Offset::Zero     = {0, 0};

    bool Offset::operator==(const Offset& other) const {
        return X == other.X && Y == other.Y;
    }

    Offset Offset::operator-() const {
        return {-X, -Y};
    }

    Offset Offset::operator+(const Offset& other) const {
        return {X + other.X, Y + other.Y};
    }

    Offset Offset::operator+(const f32 scalar) const {
        return {X + scalar, Y + scalar};
    }

    Offset Offset::operator-(const Offset& other) const {
        return {X - other.X, Y - other.Y};
    }

    Offset Offset::operator-(const f32 scalar) const {
        return {X - scalar, Y - scalar};
    }

    Offset Offset::operator*(const Offset& other) const {
        return {X + other.X, Y + other.Y};
    }

    Offset Offset::operator*(const f32 scalar) const {
        return {X * scalar, Y * scalar};
    }

    Offset Offset::operator/(const Offset& other) const {
        return {X + other.X, Y + other.Y};
    }

    Offset Offset::operator/(const f32 scalar) const {
        return {X / scalar, Y / scalar};
    }

    Offset Offset::FromDirection(const f32 direction, const f32 distance) {
        return {distance * std::cos(direction), distance * std::sin(direction)};
    }

    Offset Offset::Lerp(const Offset& a, const Offset& b, const f64 t) {
        return {Math::Lerp(a.X, b.X, t), Math::Lerp(a.Y, b.Y, t)};
    }

    /**
     *
     * @param points A list of 2D points in Cartesian space
     * @return The center point of that shape
     *
     * @link
     * https://stackoverflow.com/questions/75699024/finding-the-centroid-of-a-polygon-in-python
     * @endlink
     */
    Offset Offset::Centroid(const Vector<Offset>& points) {
        f32 signedArea = 0.f;
        f32 Cx         = 0.f;
        f32 Cy         = 0.f;
        const size_t n = points.size();

        for (size_t i = 0; i < n; i++) {
            const i32 next = (i + 1) % n;
            const f32 x0   = points.at(i).X;
            const f32 y0   = points.at(i).Y;
            const f32 x1   = points.at(next).X;
            const f32 y1   = points.at(next).Y;

            const f32 a = x0 * y1 - x1 * y0;
            signedArea += a;
            Cx += (x0 * x1) * a;
            Cy += (y0 * y1) * a;
        }

        signedArea *= 0.5f;
        Cx = (Cx / (6.0f * signedArea));
        Cy = (Cy / (6.0f * signedArea));

        return {Cx, Cy};
    }

    f64 Offset::Direction() const {
        return std::atan2(static_cast<f64>(X), static_cast<f64>(Y));
    }

    f64 Offset::Distance() const {
        return std::sqrt(X * X + Y * Y);
    }

    f64 Offset::DistanceSqr() const {
        return X * X + Y * Y;
    }

    bool Offset::IsFinite() const {
        return X != Infinity<f32>() && Y != Infinity<f32>();
    }

    bool Offset::IsInfinite() const {
        return X == Infinity<f32>() && Y == Infinity<f32>();
    }

    Offset Offset::Scale(const f32 scaleX, const f32 scaleY) const {
        return {X * scaleX, Y * scaleY};
    }

    Offset Offset::Translate(const f32 translateX, const f32 translateY) const {
        return {X + translateX, Y + translateY};
    }
}  // namespace Fuse