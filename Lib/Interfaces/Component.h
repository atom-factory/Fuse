// Author: Jake Rieger
// Created: 7/12/2024.
//

#pragma once

#include "Types.h"
#include "Traits.h"

namespace Fuse {
    class IBackend;

    class IComponent {
    public:
        virtual ~IComponent() = default;

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