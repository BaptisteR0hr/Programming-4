#include "GameObjectCommands.h"
#include "PlayerComponent.h"

namespace dae {
    void DieCommand::Execute() {
        if (m_pPlayer) m_pPlayer->Die();
    }

    void ScoreCommand::Execute() {
        if (m_pPlayer) m_pPlayer->AddScore(m_ScoreToAdd);
    }
}