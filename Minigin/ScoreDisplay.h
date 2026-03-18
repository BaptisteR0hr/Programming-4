class ScoreDisplay : public dae::IObserver {
public:
    void OnNotify(dae::GameEvent event, void* data) override {
        if (event == dae::GameEvent::ScoreChanged) {
            int newScore = *static_cast<int*>(data);
            m_textComponent->SetText("Score: " + std::to_string(newScore));
        }
    }
private:
    dae::TextComponent* m_textComponent;
};