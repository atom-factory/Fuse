// Author: Jake Rieger
// Created: 7/12/2024.
//

#pragma once
#include "PluginView.h"
#include "Traits.h"

namespace ArkVector {
    /// Root interface of an ArkVector UI app
    class IPluginCanvas : public Traits::TNotify {
    public:
        IPluginCanvas() {
            m_View = IPluginView::Create({800, 600});
            if (!m_View) {
                throw std::exception("Failed to create plugin view");
            }
        }

        virtual ~IPluginCanvas() = default;

        virtual void Draw() = 0;

    protected:
        IPluginView* m_View;
    };
}  // namespace ArkVector