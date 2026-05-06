#include "PengoComponent.h"
#include "PengoState.h"
#include "PengoStates.h"

namespace pengo {
    void PengoComponent::Update(float deltaTime) {
        if (!m_pCurrentState) return;

        auto newState = m_pCurrentState->HandleInput(this);
        if (newState) {
            ChangeState(std::move(newState));
            return;
        }

        auto updatedState = m_pCurrentState->Update(this, deltaTime);
        if (updatedState) {
            ChangeState(std::move(updatedState));
        }
    }

    void PengoComponent::ChangeState(std::unique_ptr<PengoState> newState) {
        if (m_pCurrentState) m_pCurrentState->OnExit(this);
        m_pCurrentState = std::move(newState);
        m_pCurrentState->OnEnter(this);
    }


}