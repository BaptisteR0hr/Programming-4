#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae {
    class PlayerComponent final : public BaseComponent, public Subject {
    public:
        explicit PlayerComponent(GameObject* pOwner) : BaseComponent(pOwner) {}
        virtual ~PlayerComponent() = default;

        void Update(float /*deltaTime*/ ) override {}
        void Render() const override {}

        void Die() {
            m_Lives--;
            Notify(GameEvent::PlayerDied, &m_Lives);
        }

        void AddScore(int points) {
            m_Score += points;
            Notify(GameEvent::ScoreChanged, &m_Score);
        }

        int GetScore() const { return m_Score; }
        int GetLives() const { return m_Lives; }

    private:
        int m_Lives{ 3 };
        int m_Score{ 0 };
    };
}