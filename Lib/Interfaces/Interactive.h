// Author: Jake Rieger
// Created: 7/18/2024.
//

#pragma once

namespace Fuse {
    class IInteractive {
    public:
        virtual ~IInteractive() = default;
        virtual void OnPressed() {};
        virtual void OnReleased() {};
        virtual void OnEnter() {};
        virtual void OnExit() {};
    };
}  // namespace Fuse