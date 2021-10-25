// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Entity.h"

#include "Scene.h"
#include "SceneManager.h"
#include "Components.h"

namespace Iceblur
{
	Entity::Entity(IceString name) : m_Name(name)
	{
		GenerateUniqueId();
		AddComponent(new class TransformComponent());
	}

	Entity* Entity::CreateAndAdd(IceString name)
	{
		auto entity = CreateNew(name);

		if (SceneManager::GetCurrentScene())
		{
			SceneManager::GetCurrentScene()->AddEntity(entity);
		}
		else
		{
			ICE_ERROR(Error::ETypes::A_NULLPTR, { "Current Scene" });
		}

		return entity;
	}

	void Entity::Update(float deltaTime)
	{
		if (!m_HasGeneratedId)
		{
			ICE_ERROR("Entity must be initialized first before it can be used!");
			return;
		}
	}

	void Entity::AddComponent(Component* component)
	{
		component->SetParent(this);
		m_ComponentRegistry.emplace_back(component);
	}
}
