// Author: Jake Rieger
// Created: 7/18/2024.
//

#pragma once

namespace Fuse {
    /**
     * @brief Base interface component classes can implement to signal that they should receive
     * input events.
     */
    class IInteractive {
    public:
        virtual ~IInteractive() = default;
        virtual void OnPressed() {};
        virtual void OnReleased() {};
        virtual void OnEnter() {};
        virtual void OnExit() {};
    };
}  // namespace Fuse