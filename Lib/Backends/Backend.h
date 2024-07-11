// Author: Jake Rieger
// Created: 7/11/24.
//

#pragma once

#include "Size.h"
#include "Platform/AppWindow.h"

namespace ArkVector {
    class IBackend {
    public:
        virtual ~IBackend() = default;
        virtual void Init() {}
        virtual void OnResize(const Size<u32>& size) = 0;
        virtual void OnPaint(const Size<u32>& size)  = 0;

        template<typename T>
        T* As() {
            return dynamic_cast<T*>(this);
        }

    protected:
        virtual void Shutdown() = 0;
    };
}  // namespace ArkVector