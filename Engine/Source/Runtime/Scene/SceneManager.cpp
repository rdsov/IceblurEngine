// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "SceneManager.h"

#include "Scene.h"
#include "Core/IO/Log.h"

namespace Iceblur
{
	Scene* SceneManager::m_CurrentScene;
	std::vector<Scene*> SceneManager::m_SceneRegistry;

	Scene* SceneManager::CreateNew(const SceneProps& props)
	{
		auto* scene = new Scene(props);

		ICE_PRINT("Created scene: " + scene->GetName());

		AddScene(scene);

		return scene;
	}

	void SceneManager::AddScene(Scene* scene)
	{
		ICE_CHECK_NULL(scene, "Scene");

		m_SceneRegistry.emplace_back(scene);
		ICE_PRINT("Added scene: " + scene->GetName());
	}

	void SceneManager::LoadScene(Scene* scene)
	{
		ICE_CHECK_NULL(scene, "Scene");

		//Check if the scene exists in the registry.
		auto it = std::find(m_SceneRegistry.begin(), m_SceneRegistry.end(), scene);
		if (it == m_SceneRegistry.end())
		{
			//It wasn't found, add it manually.
			AddScene(scene);
		}

		m_CurrentScene = scene;

		ICE_PRINT("Loaded scene: " + scene->GetName());
	}

	void SceneManager::Draw()
	{
		if (!m_CurrentScene)
		{
			return;
		}

		m_CurrentScene->Draw();
	}

	void SceneManager::Update(float deltaTime)
	{
		if (!m_CurrentScene)
		{
			return;
		}

		m_CurrentScene->Update(deltaTime);
	}
}
