// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"
#include "Core/CoreUtils.h"
#include "Core/Identifiable.h"

namespace Iceblur
{
	class ICE_API Entity : Identifiable
	{
	public:
		Entity(IceString name = "New Entity")
				: m_Name(name)
		{
			std::cout << "Created Entity" << std::endl;
		}

		//Creates a new entity and calls Initialize() function.
		//Returns the newly created entity.
		static Entity* CreateNew(IceString name)
		{
			auto entity = new Entity(name);
			entity->Initialize();
			return entity;
		}

		//Same as CreateNew(), but this function also adds the newly
		//created entity to the current scene.
		//If SceneManager::GetCurrentScene() is null, an error is thrown.
		static Entity* CreateAndAdd(IceString name);

		//Initializes entity with a unique identifier.
		void Initialize() override;

		void Update(float deltaTime);

		std::string GetName() const
		{
			return m_Name;
		}

	private:
		std::string m_Name;
	};
}
