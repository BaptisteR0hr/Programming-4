#pragma once
#include "PengoState.h"
#include <memory>
namespace pengo {
class IdleState final : public PengoState {
public:
    std::unique_ptr<PengoState> HandleInput(PengoComponent* player) override;
    std::unique_ptr<PengoState> Update(PengoComponent* player, float deltaTime) override;
};
}