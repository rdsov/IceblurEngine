// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"
#include "Core/CoreUtils.h"

namespace Iceblur
{
	class Entity;

	//Contains information about a scene
	struct SceneProps
	{
		std::string name;
	};

	class ICE_API Scene
	{
	public:
		explicit Scene(const SceneProps& props) : m_Props(props)
		{
		}

		NODISCARD std::string GetName() const
		{
			return m_Props.name;
		}

		void AddEntity(Entity* entity);

		void Update(float deltaTime);

	private:
		SceneProps m_Props;

		std::vector<Entity*> m_EntityRegistry;
	};
}
