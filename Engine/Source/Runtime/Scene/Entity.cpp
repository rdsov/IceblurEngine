// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Entity.h"

#include "Scene.h"
#include "SceneManager.h"

#include "Component.h"
#include "Components/TransformComponent.h"

namespace Iceblur
{
	Entity::Entity(IceString name) : m_Name(name)
	{
		GenerateUniqueId();
		AddComponent<TransformComponent>(new TransformComponent());
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

	class TransformComponent* Entity::Transform() const
	{
		return GetComponent<TransformComponent>();
	}

	void Entity::SetParentEntity(Component* component)
	{
		component->SetParentEntity(this);
	}

	bool Entity::IsComponentEssential(Component* component)
	{
		return component->IsEssential();
	}

	void Entity::RegisterComponents()
	{
		if (SceneManager::GetCurrentScene()->FindEntity(this))
		{
			SceneManager::GetCurrentScene()->RegisterEntityComponents(this);
		}
	}
}
