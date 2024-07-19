// Author: Jake Rieger
// Created: 7/11/2024.
//

#pragma once

#include "Types.h"
#include "Size.h"
#include "Backend.h"
#include "Offset.h"

namespace Fuse {
    class IPluginCanvas;

    struct ViewState {
        Size<u32> Size         = {0, 0};
        Offset CurrentMousePos = {0, 0};
        Offset LastMousePos    = {0, 0};
        i32 LastKeyDown        = -1;
        i32 LastKeyUp          = -1;
        i32 LastMouseDown      = -1;
        i32 LastMouseUp        = -1;
    };

    class IPluginView {
    public:
        explicit IPluginView(void* parent)
            : m_Backend(nullptr), m_OwningCanvas(nullptr), m_Parent(parent) {}
        virtual ~IPluginView() = default;

    public:
        virtual void Initialize() {}
        virtual void Shutdown() = 0;
        virtual void OnResize(const Size<u32>& newSize) {
            m_ViewState.Size = newSize;
        }

        virtual void OnPaint();

        virtual void OnKeyDown(const i32 keyCode) {
            m_ViewState.LastKeyDown = keyCode;
        }

        virtual void OnKeyUp(const i32 keyCode) {
            m_ViewState.LastKeyUp = keyCode;
        }

        virtual void OnMouseButtonDown(const int button, int x, int y) {
            m_ViewState.LastMouseDown = button;
        }

        virtual void OnMouseButtonUp(const int button, int x, int y) {
            m_ViewState.LastMouseUp = button;
        }

        virtual void OnMouseMove(const int x, const int y) {
            m_ViewState.LastMousePos    = m_ViewState.CurrentMousePos;
            m_ViewState.CurrentMousePos = Offset(static_cast<f32>(x), static_cast<f32>(y));
        }

    public:
        template<typename T>
        T* As() {
            static_assert(std::is_base_of_v<IPluginView, T>, "T must implement IPluginView");
            return dynamic_cast<T*>(this);
        }

        void SetOwner(IPluginCanvas* owner) {
            m_OwningCanvas = owner;
        }

        Size<u32>& GetSize() {
            return m_ViewState.Size;
        }

        ViewState& GetViewState() {
            return m_ViewState;
        }

        static IPluginView* Create(void* parent);

        [[nodiscard]] IBackend* GetBackend() const {
            return m_Backend;
        }

    protected:
        ViewState m_ViewState {};
        IBackend* m_Backend;
        IPluginCanvas* m_OwningCanvas;
        void* m_Parent;
    };
}  // namespace Fuse