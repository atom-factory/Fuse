// Author: Jake Rieger
// Created: 7/15/2024.
//

#pragma once

#include "Interfaces/Component.h"
#include "Interfaces/Interactive.h"

namespace Fuse::Component {
    class PushButton : public IComponent,
                       public IInteractive {};
}  // namespace Fuse::Component
