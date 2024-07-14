// Author: Jake Rieger
// Created: 7/14/2024.
//

#include "Box.h"

namespace ArkVector::Component {
    void Box::Draw(IBackend* backend) {
        backend->DrawRect();
        // Yup, that's literally it...
    }
}  // namespace ArkVector::Components