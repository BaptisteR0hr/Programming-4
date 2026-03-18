#include "Observer.h"
#if USE_STEAMWORKS
#include <steam_api.h>
#endif

namespace dae {
    class AchievementManager : public dae::IObserver {
    public:
        void OnNotify(dae::GameEvent event, void* data) override {
            if (event == dae::GameEvent::ScoreChanged) {
                int score = *static_cast<int*>(data);
                if (score >= 500) {
#if USE_STEAMWORKS
                    SteamUserStats()->SetAchievement("ACH_WIN_ONE_GAME");
                    SteamUserStats()->StoreStats();
#endif
                }
            }
        }
    };
}
