#pragma once
#include "PengoState.h"

namespace pengo {
    class PushingState final : public PengoState {
        float m_Timer = 0.25f;
    public:
        void OnEnter(PengoComponent* player) override {
            
        }

        std::unique_ptr<PengoState> HandleInput(PengoComponent*) override { return nullptr; }

        void Update(PengoComponent*, float deltaTime) override {
            m_Timer -= deltaTime;
            if (m_Timer <= 0) {
            }
        }
    };
}