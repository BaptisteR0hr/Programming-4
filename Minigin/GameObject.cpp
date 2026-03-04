#include <string>
#include "GameObject.h"
#include <algorithm>
#include <memory>


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

void dae::GameObject::RenderImGui()
{
    for (auto& component : m_components)
    {
        component->RenderImGui();
    }
}

void dae::GameObject::RemoveComponent(BaseComponent* pComponent)
{
	m_components.erase(std::remove_if(m_components.begin(), m_components.end(),
		[pComponent](const std::unique_ptr<BaseComponent>& comp) {
			return comp.get() == pComponent;
		}), m_components.end());
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos) {
    m_localPosition = pos;
        SetPositionDirty();
}

void dae::GameObject::SetPositionDirty() {
    m_positionIsDirty = true;
    for (auto child : m_children) {
        child->SetPositionDirty();
    }
}

const glm::vec3& dae::GameObject::GetWorldPosition() {
    if (m_positionIsDirty) {
        UpdateWorldPosition();
    }
    return m_worldPosition;
}

void dae::GameObject::UpdateWorldPosition() {
    if (m_positionIsDirty) {
        if (m_parent == nullptr) {
            m_worldPosition = m_localPosition;
        }
        else {
            m_worldPosition = m_parent->GetWorldPosition() + m_localPosition;
        }
        m_positionIsDirty = false;
    }
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition) {
    if (IsChild(parent) || parent == this || m_parent == parent) return;

        if (parent == nullptr) {
            SetLocalPosition(GetWorldPosition());
        }
        else {
            if (keepWorldPosition) {
                SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
            }
            SetPositionDirty();
        }

    if (m_parent) m_parent->RemoveChild(this);

        m_parent = parent;

        if (m_parent) m_parent->AddChild(this);
}

void dae::GameObject::AddChild(GameObject* child) {
    m_children.emplace_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child) {
    m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
}

bool dae::GameObject::IsChild(GameObject* potentialChild) const {
    if (!potentialChild) return false;
    for (auto child : m_children) {
        if (child == potentialChild || child->IsChild(potentialChild)) return true;
    }
    return false;
}
