#pragma once
#include "BaseComponent.h"
#include <string>

namespace dae {
    class TextComponent;

    class FPSComponent final : public BaseComponent {
    public:
        explicit FPSComponent(GameObject* pOwner);
        void Update(float deltaTime) override;
        void Render() const override {}
    private:
        TextComponent* m_pTextComponent;
        float m_fpsTimer{ 0.0f };
        int m_frameCount{ 0 };
    };
}