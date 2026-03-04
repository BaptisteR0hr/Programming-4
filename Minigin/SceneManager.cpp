#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(const float DeltaT)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(DeltaT);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene()
{
	m_scenes.emplace_back(new Scene());
	return *m_scenes.back();
}

void dae::SceneManager::RenderImGui()
{
	if (m_activeSceneIndex >= 0 && m_activeSceneIndex < static_cast<int>(m_scenes.size()))
	{
		m_scenes[m_activeSceneIndex]->RenderImGui();
	}
}