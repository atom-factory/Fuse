// Author: Jake Rieger
// Created: 7/11/2024.
//

#pragma once

#include "Types.h"
#include "Size.h"

namespace ArkVector {
    class IAppWindow {
    public:
        explicit IAppWindow(const Size<u32>& windowSize) : m_WindowSize(windowSize) {}
        virtual ~IAppWindow() = default;
        virtual void Initialize() {}
        virtual void Shutdown() = 0;

        template<typename T>
        T* As() {
            return dynamic_cast<T*>(this);
        }

        Size<u32>& GetSize() {
            return m_WindowSize;
        }

    protected:
        Size<u32> m_WindowSize;
    };
}  // namespace ArkVector