#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"


void dae::GameObject::Update(float deltaTime)
{ 
	for (auto& component : m_components)
	{
		component->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_components)
	{
		component->Render();
	}
}

void dae::GameObject::RemoveComponent(BaseComponent* pComponent)
{
	m_components.erase(std::remove_if(m_components.begin(), m_components.end(),
		[pComponent](const std::unique_ptr<BaseComponent>& comp) {
			return comp.get() == pComponent;
		}), m_components.end());
}
