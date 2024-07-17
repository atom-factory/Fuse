// Author: Jake Rieger
// Created: 7/11/24.
//

#pragma once

#include "Color.h"
#include "Size.h"
#include "Offset.h"

namespace Fuse {
    class IPluginView;

    class IBackend {
    public:
        virtual ~IBackend() = default;
        virtual void Initialize(IPluginView* owner) {
            SetOwner(owner);
        }
        virtual void OnResize(const Size<u32>& size) = 0;

        virtual void BeginDrawing(const Color clearColor) {}
        virtual void EndDrawing() {}

        template<typename T>
        T* As() {
            static_assert(std::is_base_of_v<IBackend, T>, "T must implement IBackend");
            return dynamic_cast<T*>(this);
        }

        void SetOwner(IPluginView* owner) {
            m_OwningView = owner;
        }

        [[nodiscard]] IPluginView* GetOwner() const {
            return m_OwningView;
        }

        virtual void
        DrawRect(const Size<u32>& size, const Offset& position, const Color& fillColor) {}
        virtual void DrawLine() {}
        virtual void DrawEllipse() {}
        virtual void DrawPath() {}
        virtual void DrawString() {}

    protected:
        virtual void Shutdown() = 0;

        IPluginView* m_OwningView = nullptr;
    };
}  // namespace Fuse