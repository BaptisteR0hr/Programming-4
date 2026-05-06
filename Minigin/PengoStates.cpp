#include "PengoStates.h"
#include "PengoComponent.h"

namespace pengo {

    MovingState::MovingState(const glm::vec2& dir)
        : m_Direction(dir)
        , m_TargetPos(0, 0)
    {
    }

    // --- IDLE ---
    std::unique_ptr<PengoState> IdleState::HandleInput(PengoComponent* player) {
        auto dir = player->GetMovementDirection();
        if (glm::length(dir) > 0.1f) return std::make_unique<MovingState>(dir);
        if (player->IsPushKeyPressed()) return std::make_unique<PushingState>();
        return nullptr;
    }

    // --- MOVING ---
    void MovingState::OnEnter(PengoComponent* player) {
        player->SetAnimation("walk");
        m_TargetPos = player->GetPosition() + (m_Direction * 16.0f);
    }

    std::unique_ptr<PengoState> MovingState::Update(PengoComponent* player, float deltaTime) {
        float speed = 64.0f;
        auto newPos = player->GetPosition() + (m_Direction * speed * deltaTime);
        player->SetPosition(newPos);

        if (glm::distance(newPos, m_TargetPos) < 1.0f) {
            player->SetPosition(m_TargetPos);
            return std::make_unique<IdleState>();
        }
        return nullptr;
    }

    // --- PUSHING ---
    void PushingState::OnEnter(PengoComponent* player) {
        m_Timer = 0.25f;
        player->SetAnimation("push");
        player->AttemptPush();
    }

    std::unique_ptr<PengoState> PushingState::Update(PengoComponent*, float deltaTime) {
        m_Timer -= deltaTime;
        if (m_Timer <= 0) return std::make_unique<IdleState>();
        return nullptr;
    }
}