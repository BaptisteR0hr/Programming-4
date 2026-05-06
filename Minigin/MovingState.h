#pragma once
#include "PengoState.h"
#include <memory>

namespace pengo {
    class MovingState final : public PengoState {
        glm::vec2 m_Dir;
        glm::vec2 m_TargetPos;
    public:
        MovingState(glm::vec2 dir) : m_Dir(dir) {}

        void OnEnter(PengoComponent* player) override;

        std::unique_ptr<PengoState> HandleInput(PengoComponent*) override { return nullptr; }

        void Update(PengoComponent* player, float deltaTime) override {
            // Beweeg de transform richting m_TargetPos
            // IF bereikt: return std::make_unique<IdleState>();
        }
    };
}