#pragma once
#include "Command.h"

namespace dae {
    class PlayerComponent;

    class DieCommand final : public Command {
        PlayerComponent* m_pPlayer;
    public:
        DieCommand(PlayerComponent* pPlayer) : m_pPlayer(pPlayer) {}
        void Execute() override;
    };

    class ScoreCommand final : public Command {
        PlayerComponent* m_pPlayer;
        int m_ScoreToAdd;
    public:
        ScoreCommand(PlayerComponent* pPlayer, int score)
            : m_pPlayer(pPlayer), m_ScoreToAdd(score) {
        }
        void Execute() override;
    };
}