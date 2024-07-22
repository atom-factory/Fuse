// Author: Jake Rieger
// Created: 7/11/24.
//

#pragma once

#include "Color.h"
#include "OldSize.h"
#include "Offset.h"

namespace Fuse {
    // Forward decs
    class IPluginView;
    struct Stroke;
    class Rectangle;

    /**
     * @brief Base interface of a rendering backend.
     *
     * Platform-specific frameworks like Direct2D and OpenGL are implemented in classes implementing
     * this interface.
     */
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

        virtual void DrawRect(const Size<u32>& size,
                              const Offset& position,
                              const Color& fillColor,
                              const Stroke& stroke,
                              const bool rounded) {}
        virtual void DrawLine() {}
        virtual void DrawEllipse(const f32 radius,
                                 const Offset& position,
                                 const Color& fillColor,
                                 const Stroke& stroke) {}
        virtual void DrawPath(const Offset& position,
                              Vector<Offset> points,
                              const Color& fillColor,
                              const Stroke& stroke) {}
        virtual void
        DrawString(const str& value, const Offset& position, const f32 size, const Color& color) {}

        virtual void DrawBoundingBox(const Rectangle& box) {}

    protected:
        virtual void Shutdown() = 0;

        IPluginView* m_OwningView = nullptr;
    };
}  // namespace Fuse