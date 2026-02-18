#pragma once
#include <string>
#include <memory>
#include "Transform.h"
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class GameObject 
	{
		Transform m_transform{};
		std::vector<std::unique_ptr<BaseComponent>> m_components{};
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

		void RemoveComponent(BaseComponent* pComponent);


		Transform& GetTransform() { return m_transform; }

		GameObject() = default;
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	};
}
