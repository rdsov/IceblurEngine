// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Scene.h"

#include "Core/IO/Log.h"
#include "Entity.h"

namespace Iceblur
{
	void Scene::Update(float deltaTime)
	{
		for (const auto& entity : m_EntityRegistry)
		{
			entity->Update(deltaTime);
		}
	}

	void Scene::AddEntity(Entity* entity)
	{
		m_EntityRegistry.emplace_back(entity);
		ICE_LOG("Added entity: " + entity->GetName());
	}
}
