// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Entity.h"

#include "Scene.h"
#include "SceneManager.h"

#include "Renderer/Renderer.h"
#include "Renderer/RenderingPipeline.h"
#include "Renderer/Shader.h"

#include "Components/TransformComponent.h"
#include "Components/MeshComponent.h"

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

		MeshComponent* mesh = GetComponent<MeshComponent>();
		if (mesh)
		{
			mesh->Draw(Renderer::GetCurrentPipeline()->GetShaderProgram());
		}

		Transform()->SetPosition(glm::vec3(Transform()->GetPosition().x + 0.001, 0, 0));
	}

	class TransformComponent* Entity::Transform() const
	{
		return GetComponent<TransformComponent>();
	}
}
