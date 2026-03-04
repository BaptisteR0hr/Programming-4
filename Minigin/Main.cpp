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
#include <memory>

namespace fs = std::filesystem;

static void load() {
    auto& scene = dae::SceneManager::GetInstance().CreateScene();

    // Achtergrond
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

    // midden Logo
    auto staticLogo = std::make_unique<dae::GameObject>();
    staticLogo->AddComponent<dae::RenderComponent>("logo.png");
    staticLogo->SetLocalPosition({ 358, 180, 0.0f });
    scene.Add(std::move(staticLogo));

    // Titel
    auto fontLarge = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
    auto titleObject = std::make_unique<dae::GameObject>();
    titleObject->AddComponent<dae::TextComponent>("Programming 4 Assignment", fontLarge);
    titleObject->SetLocalPosition({ 290, 20,0 });
    scene.Add(std::move(titleObject));

    // Benchmark
    auto benchmarkGO = std::make_unique<dae::GameObject>();
    benchmarkGO->AddComponent<dae::TrashTheCacheComponent>();
    scene.Add(std::move(benchmarkGO));
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
