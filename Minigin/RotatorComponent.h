#pragma once
#include "BaseComponent.h"

namespace dae {
    class RotatorComponent final : public BaseComponent {
    public:
        RotatorComponent(GameObject* pOwner, float radius, float speed);
        void Update(float deltaTime) override;
        void Render() const override {}

    private:
        float m_radius;
        float m_speed;
        float m_angle{ 0.0f };
    };
}