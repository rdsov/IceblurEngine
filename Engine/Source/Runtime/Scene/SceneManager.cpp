// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "SceneManager.h"

#include "Scene.h"
#include "Core/IO/Log.h"

namespace Iceblur
{
	std::vector<Scene*> SceneManager::m_SceneRegistry;

	void SceneManager::CreateNew(const SceneProps& props)
	{
		auto* scene = new Scene(props);

		ICE_INFO("Created scene: " + scene->GetName());

		AddScene(scene);
	}

	void SceneManager::AddScene(Scene* scene)
	{
		m_SceneRegistry.emplace_back(scene);
		ICE_INFO("Added scene: " + scene->GetName());
	}
}
