// Author: Jake Rieger
// Created: 7/15/2024.
//

#pragma once

#include "Types.h"

namespace ArkVector {
    /**
     * @brief Base color struct used to store float values of each color and alpha component.
     *
     * Will likely never be used directly by plugin developers.
     */
    struct BaseColor {
        f32 r;
        f32 g;
        f32 b;
        f32 a;
    };

    /**
     * @brief A 32 bit color value in ARGB format
     */
    class Color {
    public:
        Color();
        Color(f32 r, f32 g, f32 b, f32 a = 1.0);
        explicit Color(u32 color);

        /// Returns the color value as a 32-bit unsigned integer (ex. 0xFF000000 for black)
        [[nodiscard]] u32 Value() const;
        /// Gets the luminance value as a 32-bit float
        [[nodiscard]] f32 Luminance() const;
        /// Creates a new color from the source color with the provided alpha
        [[nodiscard]] Color WithAlpha(u32 a) const;
        /// Creates a new color from the source color with the provided alpha
        [[nodiscard]] Color WithAlpha(f32 a) const;
        /// Creates a new color from the source color with the provided red value
        [[nodiscard]] Color WithRed(u32 r) const;
        /// Creates a new color from the source color with the provided red value
        [[nodiscard]] Color WithRed(f32 r) const;
        /// Creates a new color from the source color with the provided green value
        [[nodiscard]] Color WithGreen(u32 g) const;
        /// Creates a new color from the source color with the provided green value
        [[nodiscard]] Color WithGreen(f32 g) const;
        /// Creates a new color from the source color with the provided blue value
        [[nodiscard]] Color WithBlue(u32 b) const;
        /// Creates a new color from the source color with the provided blue value
        [[nodiscard]] Color WithBlue(f32 b) const;
        /// Gets the current color in its greyscale format
        [[nodiscard]] Color Greyscale() const;

        /// Creates a new color by blending two provided colors including their alpha channels
        static Color AlphaBlend(const Color& foreground, const Color& background);
        /// Gets the alpha value as an unsigned integer from the provided opacity value
        static u32 GetAlphaFromOpacity(f32 opacity);
        /// Linearly interpolates between two provided colors by a constant `t`
        static Color Lerp(const Color& a, const Color& b, f32 t);
        /// Gamma corrects specified color component `c`
        static f32 LinearizeComponent(f32 c);

        /// Returns red component
        [[nodiscard]] f32 Red() const {
            return m_BaseColor.r;
        }
        /// Returns green component
        [[nodiscard]] f32 Green() const {
            return m_BaseColor.g;
        }
        /// Returns blue component
        [[nodiscard]] f32 Blue() const {
            return m_BaseColor.g;
        }
        /// Returns alpha component
        [[nodiscard]] f32 Alpha() const {
            return m_BaseColor.a;
        }

    private:
        BaseColor m_BaseColor;
    };

    namespace Colors {
        inline static auto White       = Color(0xFFFFFFFF);
        inline static auto Black       = Color(0xFF000000);
        inline static auto Red         = Color(0xFFFF0000);
        inline static auto Yellow      = Color(0xFFFFFF00);
        inline static auto Green       = Color(0xFF00FF00);
        inline static auto Cyan        = Color(0xFF00FFFF);
        inline static auto Blue        = Color(0xFF0000FF);
        inline static auto Magenta     = Color(0xFFFF00FF);
        inline static auto Transparent = Color(0x00000000);
    };  // namespace Colors

}  // namespace ArkVector
