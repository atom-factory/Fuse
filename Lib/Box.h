// Author: Jake Rieger
// Created: 7/14/2024.
//

#pragma once

#include "Interfaces/Component.h"
#include "Traits.h"

using namespace ArkVector::Traits;

namespace ArkVector::Component {
    class Box final : public IComponent,
                      public TSingleChild {
    public:
        void Draw(IBackend* backend) override;
    };

}  // namespace ArkVector::Component
