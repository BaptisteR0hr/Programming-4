#pragma once
#include <memory>

namespace pengo {
    class PengoComponent;

    class PengoState {
    public:
        virtual ~PengoState() = default;
        virtual void OnEnter(PengoComponent*) {}
        virtual void OnExit(PengoComponent*) {}
        virtual std::unique_ptr<PengoState> HandleInput(PengoComponent* player) = 0;
        virtual std::unique_ptr<PengoState> Update(PengoComponent* player, float deltaTime) = 0;
    };
}