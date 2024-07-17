// Author: Jake Rieger
// Created: 7/11/2024.
//

#pragma once

#include "Types.h"
#include "Size.h"
#include "Backend.h"
#include "Component.h"

namespace Fuse {
    class IPluginCanvas;

    class IPluginView {
    public:
        explicit IPluginView(void* parent)
            : m_WindowSize({0, 0}), m_Backend(nullptr), m_OwningCanvas(nullptr), m_Parent(parent) {}
        virtual ~IPluginView() = default;
        virtual void Initialize() {}
        virtual void Shutdown() = 0;

        virtual void OnResize(const Size<u32>& newSize) {
            m_WindowSize = newSize;
        }

        virtual void OnPaint(const Color& backgroundColor) const;

        template<typename T>
        T* As() {
            static_assert(std::is_base_of_v<IPluginView, T>, "T must implement IPluginView");
            return dynamic_cast<T*>(this);
        }

        void SetOwner(IPluginCanvas* owner) {
            m_OwningCanvas = owner;
        }

        Size<u32>& GetSize() {
            return m_WindowSize;
        }

        static IPluginView* Create(void* parent);

        [[nodiscard]] IBackend* GetBackend() const {
            return m_Backend;
        }

    protected:
        Size<u32> m_WindowSize;
        IBackend* m_Backend;
        IPluginCanvas* m_OwningCanvas;
        void* m_Parent;
    };
}  // namespace Fuse