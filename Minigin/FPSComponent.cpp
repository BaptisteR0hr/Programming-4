#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"  
#include <iomanip>
#include <sstream>


dae::FPSComponent::FPSComponent(GameObject* pOwner) :
    BaseComponent(pOwner),
    m_pTextComponent(nullptr)
{
    m_pTextComponent = pOwner->GetComponent<TextComponent>();
    if (!m_pTextComponent) {
        throw std::runtime_error("FPSComponent: TextComponent niet gevonden op GameObject!");
    }
}

void dae::FPSComponent::Update(float deltaTime) {
    m_fpsTimer += deltaTime;
    m_frameCount++;

    if (m_fpsTimer >= 0.5f) {
        float fps = static_cast<float>(m_frameCount) / m_fpsTimer;
        if (m_pTextComponent) {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(1) << fps << " FPS";
            m_pTextComponent->SetText(ss.str());
        }

        m_frameCount = 0;
        m_fpsTimer = 0.0f;
    }
}