#pragma once

namespace dae {
    class GameObject;

    class BaseComponent {
    public:
        explicit BaseComponent(GameObject* pOwner);
        virtual ~BaseComponent() = default;

        virtual void Update(float deltaTime) = 0;
        virtual void Render() const {};

        BaseComponent(const BaseComponent& other) = delete;
        BaseComponent(BaseComponent&& other) = delete;
        BaseComponent& operator=(const BaseComponent& other) = delete;
        BaseComponent& operator=(BaseComponent&& other) = delete;
    protected:
       
        GameObject* GetOwner() const { return m_pOwner; }

    private:
        GameObject* m_pOwner;
    };
}