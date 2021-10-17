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
		static void CreateNew(const SceneProps& props);

		static void AddScene(Scene* scene);

	private:
		static std::vector<Scene*> m_SceneRegistry;
	};
}
