#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "RotatorComponent.h"
#include <filesystem>
#include "TrashTheCacheComponent.h"
#include "InputManager.h"
#include "Command.h"         
#include "GameObjectCommands.h"
#include "PlayerComponent.h"
#include "UIObservers.h"
#include "AchievementManager.h"
#include "Observer.h"
#include <SDL3/SDL_scancode.h>
#include <memory>

namespace fs = std::filesystem;

static void load() {
    auto& scene = dae::SceneManager::GetInstance().CreateScene();
    static std::vector<std::shared_ptr<void>> observerStorage;

    // BACKGROUND
    auto background = std::make_unique<dae::GameObject>();
    background->AddComponent<dae::RenderComponent>("background.png");
    background->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
    scene.Add(std::move(background));

    // FPS Counter 
    auto fpsObject = std::make_unique<dae::GameObject>();
    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
    fpsObject->AddComponent<dae::TextComponent>("", font);
    fpsObject->AddComponent<dae::FPSComponent>();
    fpsObject->SetLocalPosition({ 10.0f, 10.0f, 0.0f });
    scene.Add(std::move(fpsObject));

    // MID LOGO
    auto staticLogo = std::make_unique<dae::GameObject>();
    staticLogo->AddComponent<dae::RenderComponent>("logo.png");
    staticLogo->SetLocalPosition({ 358, 180, 0.0f });
    scene.Add(std::move(staticLogo));

    // TITLE
    auto fontLarge = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
    auto titleObject = std::make_unique<dae::GameObject>();
    titleObject->AddComponent<dae::TextComponent>("Programming 4 Assignment", fontLarge);
    titleObject->SetLocalPosition({ 290, 20,0 });
    scene.Add(std::move(titleObject));

    // PLAYER 1 SETUP
    auto player1 = std::make_unique<dae::GameObject>();
    auto pc1 = player1->AddComponent<dae::PlayerComponent>();
    scene.Add(std::move(player1));

    // LIVES UI PLAYER 1
    auto p1LivesUI = std::make_unique<dae::GameObject>();
    auto p1LivesText = p1LivesUI->AddComponent<dae::TextComponent>("P1 Lives: 3", font);
    p1LivesUI->SetLocalPosition({ 10, 40, 0 });

    auto p1LivesObs = std::make_shared<dae::LivesDisplay>(p1LivesText);
    pc1->AddObserver(p1LivesObs.get());
    observerStorage.push_back(p1LivesObs);
    scene.Add(std::move(p1LivesUI));

    // SCORE UI PLAYER 1
    auto p1ScoreUI = std::make_unique<dae::GameObject>();
    auto p1ScoreText = p1ScoreUI->AddComponent<dae::TextComponent>("P1 Score: 0", font);
    p1ScoreUI->SetLocalPosition({ 10, 60, 0 });

    auto p1ScoreObs = std::make_shared<dae::ScoreDisplay>(p1ScoreText);
    pc1->AddObserver(p1ScoreObs.get());
    observerStorage.push_back(p1ScoreObs);
    scene.Add(std::move(p1ScoreUI));


	// PLAYER 2 SETUP
    auto player2 = std::make_unique<dae::GameObject>();
    auto pc2 = player2->AddComponent<dae::PlayerComponent>();
    scene.Add(std::move(player2));

	// LIVES UI PLAYER 2
    auto p2LivesUI = std::make_unique<dae::GameObject>();
    auto p2LivesText = p2LivesUI->AddComponent<dae::TextComponent>("P2 Lives: 3", font);
    p2LivesUI->SetLocalPosition({ 10, 90, 0 });

    auto p2LivesObs = std::make_shared<dae::LivesDisplay>(p2LivesText);
    pc2->AddObserver(p2LivesObs.get());
    observerStorage.push_back(p2LivesObs);
    scene.Add(std::move(p2LivesUI));

	// SCORE UI PLAYER 2
    auto p2ScoreUI = std::make_unique<dae::GameObject>();
    auto p2ScoreText = p2ScoreUI->AddComponent<dae::TextComponent>("P2 Score: 0", font);
    p2ScoreUI->SetLocalPosition({ 10, 110, 0 });

    auto p2ScoreObs = std::make_shared<dae::ScoreDisplay>(p2ScoreText);
    pc2->AddObserver(p2ScoreObs.get());
    observerStorage.push_back(p2ScoreObs);
    scene.Add(std::move(p2ScoreUI));


	// STEAM ACHIEVEMENT MANAGER
    auto steamManager = std::make_shared<dae::AchievementManager>();
    pc1->AddObserver(steamManager.get());
    pc2->AddObserver(steamManager.get());
    observerStorage.push_back(steamManager);


    // INPUT BINDINGS
    auto& input = dae::InputManager::GetInstance();

    input.BindCommand({ SDL_SCANCODE_K, dae::ControllerButton::None, dae::KeyState::Pressed, false },
        std::make_unique<dae::DieCommand>(pc1));

    input.BindCommand({ SDL_SCANCODE_L, dae::ControllerButton::None, dae::KeyState::Pressed, false },
        std::make_unique<dae::ScoreCommand>(pc1, 100));
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
