#pragma once
#include "BaseComponent.h"
#include <memory>
#include <utility>
#include <glm.hpp>

namespace pengo {
    class PengoState; 

    class PengoComponent final : public dae::BaseComponent {
    public:
        void Update(float deltaTime) override;
        void ChangeState(std::unique_ptr<PengoState> newState);

        
        glm::vec2 GetPosition() const { return GetOwner()->GetLocalPosition(); }
        void SetPosition(const glm::vec2& pos) { GetOwner()->SetLocalPosition(pos.x, pos.y, 0); }

        glm::vec2 GetMovementDirection() const { return m_MovementDir; }
        bool IsPushKeyPressed() const { return m_PushPressed; }

        void SetAnimation(const std::string& animName) { /* later implementeren */ }
        void AttemptPush() { /* later implementeren */ }

    private:
        glm::vec2 m_MovementDir{};
        bool m_PushPressed{ false };

        std::unique_ptr<PengoState> m_pCurrentState;
    };
}