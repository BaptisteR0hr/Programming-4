#pragma once
#include "PengoState.h"
#include <glm.hpp> 
#include <string>

namespace pengo {
    class PengoComponent;

    class IdleState final : public PengoState {
    public:
        IdleState() = default;
        ~IdleState() override = default;
        std::unique_ptr<PengoState> HandleInput(PengoComponent* player) override;
        std::unique_ptr<PengoState> Update(PengoComponent* player, float deltaTime) override;
    };

    class MovingState final : public PengoState {
    public:
        explicit MovingState(const glm::vec2& dir); 
        ~MovingState() override = default;

        void OnEnter(PengoComponent* player) override;
        std::unique_ptr<PengoState> HandleInput(PengoComponent*) override { return nullptr; }
        std::unique_ptr<PengoState> Update(PengoComponent* player, float deltaTime) override;

    private:
        glm::vec2 m_Direction;
        glm::vec2 m_TargetPos;
    };

    class PushingState final : public PengoState {
    public:
        PushingState() = default;
        ~PushingState() override = default;
        void OnEnter(PengoComponent* player) override;
        std::unique_ptr<PengoState> HandleInput(PengoComponent*) override { return nullptr; }
        std::unique_ptr<PengoState> Update(PengoComponent* player, float deltaTime) override;
    private:
        float m_Timer = 0.25f;
    };
}