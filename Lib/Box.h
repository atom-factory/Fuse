// Author: Jake Rieger
// Created: 7/14/2024.
//

#pragma once

#include "Interfaces/Component.h"
#include "Interfaces/Backend.h"

namespace ArkVector::Component {

    class Box final : public IComponent {
    public:
        void Draw(IBackend* backend) override;
    };

}  // namespace ArkVector::Component
