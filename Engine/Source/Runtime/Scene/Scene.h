// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"
#include "Core/CoreUtils.h"

namespace Iceblur
{
	class Entity;

	class MeshComponent;

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

		//Adds entity to the registry and calls RegisterEntityComponents()
		void AddEntity(Entity* entity);

		//Checks entity's components and registers them if needed.
		//Call this function if you've added new components after
		//you have called AddEntity()
		void RegisterEntityComponents(Entity* entity);

		//Loops through the entity registry and returns true if the entity was found.
		inline bool FindEntity(Entity* entity)
		{
			for (const auto& e : m_EntityRegistry)
			{
				if (e == entity)
				{
					return true;
				}
			}

			return false;
		}

	private:
		void Draw();

		void Update(float deltaTime);

	private:
		SceneProps m_Props;

		std::vector<Entity*> m_EntityRegistry;
		std::vector<MeshComponent*> m_MeshesToRender;

		friend class SceneManager;
	};
}
