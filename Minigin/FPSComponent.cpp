#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"  
#include <iomanip>
#include <sstream>

dae::FPSComponent::FPSComponent(GameObject* pOwner) : BaseComponent(pOwner) {}

void dae::FPSComponent::Update(float deltaTime) {
    m_fpsTimer += deltaTime;
    m_frameCount++;

    if (m_fpsTimer >= 0.5f) {
        float fps = static_cast<float>(m_frameCount) / m_fpsTimer;

        auto textComp = GetOwner()->GetComponent<TextComponent>();
        if (textComp) {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(1) << fps << " FPS";
            textComp->SetText(ss.str());
        }

        m_frameCount = 0;
        m_fpsTimer = 0.0f;
    }
}