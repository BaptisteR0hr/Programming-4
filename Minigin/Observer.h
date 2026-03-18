#pragma once
#include <vector>
#include <algorithm>

namespace dae {
    enum class GameEvent {
        PlayerDied,
        ScoreChanged,
        AchievementUnlocked
    };

    class IObserver {
    public:
        virtual ~IObserver() = default;
        virtual void OnNotify(GameEvent event, void* data = nullptr) = 0;
    };

    class Subject {
    public:
        void AddObserver(IObserver* observer) { m_observers.push_back(observer); }
        void RemoveObserver(IObserver* observer) {
            m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
        }
    protected:
        void Notify(GameEvent event, void* data = nullptr) {
            for (auto observer : m_observers) {
                if (observer) observer->OnNotify(event, data);
            }
        }
    private:
        std::vector<IObserver*> m_observers;
    };
}