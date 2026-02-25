#pragma once
#include <memory>
#include <vector> 
#include "Transform.h"
#include "BaseComponent.h"


namespace dae
{
	class Texture2D;
	class GameObject 
	{
		Transform m_transform{};
		std::vector<std::unique_ptr<BaseComponent>> m_components{};
		bool m_isDead = false;

		GameObject* m_parent{ nullptr };
		std::vector<GameObject*> m_children{};

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
		bool IsChild(GameObject* potentialChild) const;

		glm::vec3 m_localPosition{};
		glm::vec3 m_worldPosition{};
		bool m_positionIsDirty{ true };

		void UpdateWorldPosition();
	public:
		virtual void Update(float deltaTime);
		virtual void Render() const;
		
		template <typename T, typename... Args>
		T* AddComponent(Args&&... args) {
			auto component = std::make_unique<T>(this, std::forward<Args>(args)...);
			T* ptr = component.get();
			m_components.push_back(std::move(component));
			return ptr;
		}

		template <typename T>
		T* GetComponent() const {
			for (auto& component : m_components) {
				T* result = dynamic_cast<T*>(component.get());
				if (result) return result;
			}
			return nullptr;
		}

		void SetDestroy() { m_isDead = true; }
		bool IsDead() const { return m_isDead; }
		void RemoveComponent(BaseComponent* pComponent);

		void SetParent(GameObject* parent, bool keepWorldPosition);
		GameObject* GetParent() const { return m_parent; }
		size_t GetChildCount() const { return m_children.size(); }
		GameObject* GetChildAt(int index) const { return m_children[index]; }

		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3& GetWorldPosition();
		void SetPositionDirty();

		Transform& GetTransform() { return m_transform; }

		GameObject() = default;
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	};
}
