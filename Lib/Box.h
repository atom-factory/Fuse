// Author: Jake Rieger
// Created: 7/14/2024.
//

#pragma once

#include "Traits.h"
#include "Interfaces/Component.h"
#include "Interfaces/Backend.h"

using namespace ArkVector::Traits;

namespace ArkVector::Component {
    class Box final : public IComponent,
                      public TSingleChild {
    public:
        void Draw(IBackend* backend) override;
    };

}  // namespace ArkVector::Component
