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
#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
    auto& scene = dae::SceneManager::GetInstance().CreateScene();

    auto backgroundObject = std::make_unique<dae::GameObject>();
    backgroundObject->AddComponent<dae::RenderComponent>("background.png");
    scene.Add(std::move(backgroundObject));

    auto logoObject = std::make_unique<dae::GameObject>();
    logoObject->AddComponent<dae::RenderComponent>("logo.png");
    logoObject->GetTransform().SetPosition(358, 180);
    scene.Add(std::move(logoObject));

    auto fontLarge = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
    auto titleObject = std::make_unique<dae::GameObject>();
    titleObject->AddComponent<dae::TextComponent>("Programming 4 Assignment", fontLarge);
    titleObject->GetTransform().SetPosition(290, 20);
    scene.Add(std::move(titleObject));

    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);

    auto fpsObject = std::make_unique<dae::GameObject>();
    fpsObject->AddComponent<dae::TextComponent>("Calculating...", font);
    fpsObject->AddComponent<dae::FPSComponent>();
    fpsObject->GetTransform().SetPosition(10, 10);

    scene.Add(std::move(fpsObject));
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
