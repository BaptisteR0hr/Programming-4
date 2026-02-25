#include "RotatorComponent.h"
#include "GameObject.h"
#include <cmath>

dae::RotatorComponent::RotatorComponent(GameObject* pOwner, float radius, float speed)
    : BaseComponent(pOwner), m_radius(radius), m_speed(speed) {
}

void dae::RotatorComponent::Update(float deltaTime) {
    m_angle += m_speed * deltaTime;

    float x = std::cos(m_angle) * m_radius;
    float y = std::sin(m_angle) * m_radius;

    GetOwner()->SetLocalPosition(glm::vec3{ x, y, 0.0f });
}