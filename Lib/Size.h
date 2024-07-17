// Author: Jake Rieger
// Created: 7/10/2024.
//

#pragma once

#include "Types.h"
#include "Offset.h"

#include <complex>

namespace Fuse {
    /// TODO: Implement operator overloads
    template<typename T = int>
    class Size {
    public:
        Size(T width, T height);

        static Size Copy(Size& other);
        static Size FromRadius(T radius);
        static Size Square(T dimension);
        static Size FromHeight(T height);
        static Size FromWidth(T width);

        f64 GetAspectRatio();
        f64 GetHypotenuse();

        template<typename newT>
        Size<newT> To();

        Offset AsOffset();
        void Set(T x, T y);

        T Width;
        T Height;
    };

    template<typename T>
    Size<T>::Size(T width, T height) : Width(width), Height(height) {}

    template<typename T>
    Size<T> Size<T>::Copy(Size& other) {
        return Size(other.Width, other.Height);
    }

    template<typename T>
    Size<T> Size<T>::FromRadius(T radius) {
        return Size(radius * 2, radius * 2);
    }

    template<typename T>
    Size<T> Size<T>::Square(T dimension) {
        return Size(dimension, dimension);
    }

    template<typename T>
    Size<T> Size<T>::FromHeight(T height) {
        return Size(std::numeric_limits<T>::max(), height);
    }

    template<typename T>
    Size<T> Size<T>::FromWidth(T width) {
        return Size(width, std::numeric_limits<T>::max());
    }

    template<typename T>
    f64 Size<T>::GetAspectRatio() {
        return static_cast<f64>(Width) / static_cast<f64>(Height);
    }

    template<typename T>
    f64 Size<T>::GetHypotenuse() {
        T aSqrd = Height * Height;
        T bSqrd = Width * Width;
        return std::sqrt(aSqrd + bSqrd);
    }

    template<typename T>
    template<typename newT>
    Size<newT> Size<T>::To() {
        return Size<newT>(static_cast<newT>(Width), static_cast<newT>(Height));
    }

    template<typename T>
    Offset Size<T>::AsOffset() {
        return Offset(Width, Height);
    }

    template<typename T>
    void Size<T>::Set(T x, T y) {
        Width  = x;
        Height = y;
    }
}  // namespace Fuse