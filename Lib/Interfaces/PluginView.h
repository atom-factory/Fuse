// Author: Jake Rieger
// Created: 7/11/2024.
//

#pragma once

#include "Types.h"
#include "Size.h"
#include "Backend.h"

namespace ArkVector {
    class IPluginView {
    public:
        explicit IPluginView(const Size<u32>& windowSize)
            : m_WindowSize(windowSize), m_Backend(nullptr) {}
        virtual ~IPluginView() = default;
        virtual void Initialize() {}
        virtual void Shutdown() = 0;

        virtual void OnResize(const Size<u32>& newSize) {
            m_WindowSize = newSize;
        }

        virtual void OnPaint() = 0;

        template<typename T>
        T* As() {
            static_assert(std::is_base_of_v<IPluginView, T>, "T must implement IPluginView");
            return dynamic_cast<T*>(this);
        }

        Size<u32>& GetSize() {
            return m_WindowSize;
        }

        static IPluginView* Create(const Size<u32>& windowSize);

    protected:
        Size<u32> m_WindowSize;
        IBackend* m_Backend;
    };
}  // namespace ArkVector