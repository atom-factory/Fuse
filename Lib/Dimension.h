// Author: Jake Rieger
// Created: 7/20/2024.
//

#pragma once

#include "Types.h"

namespace Fuse {
    struct IUnit {
        virtual ~IUnit()                    = default;
        virtual f32 Convert(f32 value, f32) = 0;
    };

    struct PercentUnit : IUnit {
        f32 Convert(const f32 value, const f32 screenSize) override {
            return screenSize * value;
        }
    };

    struct PixelUnit : IUnit {
        f32 Convert(const f32 value, f32) override {
            return value;
        }
    };

    /**
     * @brief A template class for size and position dimensions
     *
     * @tparam Unit Type of unit to use, either `PercentUnit` or `PixelUnit`. Default is
     * `PercentUnit`.
     *
     * @todo Actually implement this across the rest of the library classes.
     */
    template<typename Unit = PercentUnit>
    class Dimension {
    public:
        explicit Dimension(const f32 val) : Value(val) {
            static_assert(std::is_base_of_v<IUnit, Unit>, "Unit must implement IUnit");
        }

        f32 Value;

        f32 ToScreenPixels(f32 screenSize) const {
            return Unit::Convert(Value, screenSize);
        }
    };
}  // namespace Fuse