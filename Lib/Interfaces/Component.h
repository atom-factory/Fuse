// Author: Jake Rieger
// Created: 7/12/2024.
//

#pragma once

namespace ArkVector {
    class IBackend;

    class IComponent {
    public:
        virtual ~IComponent() = default;

        virtual void Draw(IBackend* backend) = 0;
    };
}  // namespace ArkVector