// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Scene.h"

#include "Core/VTime.h"
#include "Core/IO/Log.h"

#include "Entity.h"
#include "Components/CameraComponent.h"
#include "Components/MeshComponent.h"

#include "Renderer/Renderer.h"
#include "Renderer/RenderingPipeline.h"
#include "Renderer/Shader.h"

namespace Iceblur
{
	void Scene::AddEntity(Entity* entity)
	{
		m_EntityRegistry.emplace_back(entity);

		RegisterEntityComponents(entity);

		ICE_LOG("Added entity: " + entity->GetName());
	}

	void Scene::RegisterEntityComponents(Entity* entity)
	{
		auto meshComponent = entity->GetComponent<MeshComponent>();
		if (meshComponent)
		{
			m_MeshesToRender.emplace_back(meshComponent);
			return;
		}

		auto cameraComponent = entity->GetComponent<CameraComponent>();
		if (cameraComponent)
		{
			m_CameraRegistry.emplace_back(cameraComponent);
			return;
		}
	}

	void Scene::Update(float deltaTime)
	{
		Draw();

		for (const auto& entity : m_EntityRegistry)
		{
			entity->Update(deltaTime);
		}
	}

	void Scene::Draw()
	{
		for (const auto& camera : m_CameraRegistry)
		{
			camera->Update(VTime::GetDeltaTime());
		}

		for (const auto& mesh : m_MeshesToRender)
		{
			mesh->Draw(Renderer::GetCurrentPipeline()->GetShaderProgram());
		}
	}
}
