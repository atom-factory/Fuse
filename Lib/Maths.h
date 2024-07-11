// Author: Jake Rieger
// Created: 7/10/2024.
//

#pragma once

#include "Types.h"

#include <stdexcept>

namespace ArkVector::Math {
    template<typename T>
    constexpr bool IsFinite(T val) {
        static_assert(std::is_arithmetic_v<T>, "T must be arithmetic type");
        return val != Infinity<T>() && val != -Infinity<T>();
    }

    template<typename T>
    T Lerp(T a, T b, f64 t) {
        static_assert(std::is_arithmetic_v<T>, "T must be arithmetic type");

        if (!IsFinite(a) || !IsFinite(b) || !IsFinite(t)) {
            throw std::invalid_argument("Input values must be finite.");
        }

        if (a == b) {
            return a;
        }

        return static_cast<T>(a * (1.0 - t) + b * t);
    }
}  // namespace ArkVector::Math