// Author: Jake Rieger
// Created: 7/18/2024.
//

#pragma once

#include "Types.h"

namespace Fuse {
    struct Font {
        Path PathOnDisk;
        str Name;
        f32 Size;
        u32 Weight;
    };
}  // namespace Fuse