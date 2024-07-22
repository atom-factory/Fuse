// Author: Jake Rieger
// Created: 7/12/2024.
//

#pragma once

#include "Types.h"
#include "Traits.h"

namespace Fuse {
    // Forward decs
    class IBackend;

    /**
     * @brief Base interface of a render-able object.
     *
     * Components are analogous to components in web frameworks like React and Flutter.
     * Components can have any number of children and the renderer traverses breadth-first the UI
     * from a root component as a tree of n components.
     */
    class IComponent {
    public:
        virtual ~IComponent() {
            for (const auto child : m_Children) {
                delete child;
            }
        }

        /**
         * @brief The only required method classes implementing this interface must define. It's
         * what describes the actual visuals of the component.
         *
         * @param backend Provided to allow interfacing with the renderer.
         */
        virtual void Draw(IBackend* backend) = 0;

        bool HasChild() {
            const auto thisPtr = dynamic_cast<Traits::TSingleChild*>(this);
            return thisPtr != nullptr;
        }

        bool HasChildren() {
            const auto thisPtr = dynamic_cast<Traits::TMultiChild*>(this);
            return thisPtr != nullptr;
        }

        void AddChild(IComponent* component) {
            m_Children.push_back(component);
        }

        IComponent* GetChild() const {
            if (m_Children.empty()) {
                return nullptr;
            }

            return m_Children.front();
        }

        Option<Vector<IComponent*>> GetChildren() {
            if (m_Children.empty()) {
                return kNone;
            }

            return m_Children;
        }

    protected:
        std::vector<IComponent*> m_Children;
    };
}  // namespace Fuse