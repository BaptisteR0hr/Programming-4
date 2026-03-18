#pragma once
#include "Observer.h"
#include "TextComponent.h"
#include <string>

namespace dae {
    class LivesDisplay : public IObserver {
        TextComponent* m_pText;
    public:
        LivesDisplay(TextComponent* text) : m_pText(text) {}
        void OnNotify(GameEvent event, void* data) override {
            if (event == GameEvent::PlayerDied && data) {
                int lives = *static_cast<int*>(data);
                m_pText->SetText("Lives: " + std::to_string(lives));
            }
        }
    };

    class ScoreDisplay : public IObserver {
        TextComponent* m_pText;
    public:
        ScoreDisplay(TextComponent* text) : m_pText(text) {}
        void OnNotify(GameEvent event, void* data) override {
            if (event == GameEvent::ScoreChanged && data) {
                int score = *static_cast<int*>(data);
                m_pText->SetText("Score: " + std::to_string(score));
            }
        }
    };
}