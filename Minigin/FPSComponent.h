#pragma once
#include "BaseComponent.h"
#include <string>

namespace dae {
    class TextComponent;

    class FPSComponent final : public BaseComponent {
    public:
        explicit FPSComponent(GameObject* pOwner);
        void Update(float deltaTime) override;
    private:
        float m_fpsTimer{ 0.0f };
        int m_frameCount{ 0 };
    };
}