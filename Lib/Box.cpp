// Author: Jake Rieger
// Created: 7/14/2024.
//

#include "Box.h"
#include "Interfaces/Backend.h"
#include "Interfaces/PluginView.h"

namespace ArkVector::Component {
    void Box::Draw(IBackend* backend) {
        const auto size     = backend->GetOwner()->GetSize();
        const auto position = Offset(20, 20);
        backend->DrawRect(size, position, Color(0xFF0A0B10));
    }
}  // namespace ArkVector::Component