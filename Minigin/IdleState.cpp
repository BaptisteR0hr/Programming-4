#include "IdleState.h"
#include "MovingState.h"  
#include "PushingState.h" 
#include "PengoComponent.h"
#include <memory>

namespace pengo {

    std::unique_ptr<PengoState> IdleState::HandleInput(PengoComponent* player) {
        auto dir = player->GetMovementDirection();

        if (glm::length(dir) > 0.1f) {
            return std::make_unique<MovingState>(dir);
        }

        if (player->IsPushKeyPressed()) {
            return std::make_unique<PushingState>();
        }

        return nullptr;
    }

    std::unique_ptr<PengoState> IdleState::Update(PengoComponent*, float) {
        return nullptr;
    }
}