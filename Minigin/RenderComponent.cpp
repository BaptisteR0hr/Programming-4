#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

dae::RenderComponent::RenderComponent(GameObject* pOwner, const std::string& filename)
    : BaseComponent(pOwner) {
    m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::Render() const {
    const auto& pos = GetOwner()->GetTransform().GetPosition();
    Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}