// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"

namespace Iceblur
{
	struct SceneProps;

	class Scene;

	class ICE_API SceneManager
	{
	public:
		//Creates a new scene with specified properties and adds it to the scene registry.
		//Returns the newly created scene.
		static Scene* CreateNew(const SceneProps& props);

		//Adds a scene to the registry.
		//Note: This function does not load the scene.
		static void AddScene(Scene* scene);

		//Loads a scene and assigns it to m_CurrentScene.
		//If it was not found in the registry, it will be automatically added.
		static void LoadScene(Scene* scene);

		//Updates the current scene.
		static void Update(float deltaTime);

		static Scene* GetCurrentScene()
		{
			return m_CurrentScene;
		}

	private:
		static Scene* m_CurrentScene;
		static std::vector<Scene*> m_SceneRegistry;
	};
}
