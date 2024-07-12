// Author: Jake Rieger
// Created: 7/11/2024.
//

#pragma once

#include "Platform.h"
#include "Backend.h"

namespace ArkVector {
    class Direct2DBackend final : public IBackend {
    public:
        void Init() override;
        void OnResize(const Size<u32>& size) override;
        void OnPaint(const Size<u32>& size) override;

        void DrawRect() override;
        void DrawEllipse() override;
        void DrawLine() override;
        void DrawPath() override;
        void DrawString() override;

    protected:
        void Shutdown() override;
    };
}  // namespace ArkVector
