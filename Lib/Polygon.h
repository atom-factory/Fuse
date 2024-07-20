// Author: Jake Rieger
// Created: 7/20/2024.
//

#pragma once

#include "Types.h"
#include "Offset.h"

// TODO: Implement an actual Polygon class
namespace Fuse::Polygon {
    inline f64 CalculateArea(const Vector<Offset>& points) {
        const auto n = points.size();
        f64 area     = 0.0;

        for (i32 i = 0; i < n; ++i) {
            const i32 j = (i + 1) % n;
            area += points.at(i).X * points.at(j).Y;
            area -= points.at(j).X * points.at(i).Y;
        }

        area /= 2.0;  // Shoelace formula for area
        return area;
    }

    inline Offset CalculateCenter(const Vector<Offset>& points) {
        const auto n = points.size();
        f64 cX = 0.0, cY = 0.0;
        const f64 area   = CalculateArea(points);
        const f64 factor = 1 / (6 * area);

        for (i32 i = 0; i < n; ++i) {
            const i32 j     = (i + 1) % n;
            const f64 cross = points.at(i).X * points.at(j).Y - points.at(j).X * points.at(i).Y;
            cX += (points.at(i).X + points.at(j).X) * cross;
            cY += (points.at(i).Y + points.at(j).Y) * cross;
        }

        cX *= factor;
        cY *= factor;

        return Offset(cX, cY);
    }
}  // namespace Fuse::Polygon