// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Entity.h"

#include "Core/IO/Log.h"
#include "Scene.h"
#include "SceneManager.h"

namespace Iceblur
{
	void Entity::Initialize()
	{
		GenerateUniqueId();
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

		//ICE_LOG(m_Name + " updated");
	}
}
