// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Renderer.h"

#include "RenderingPipeline.h"
#include "Core/IO/Log.h"
#include "Event/EventSystem.h"

#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Scene/Components/CameraComponent.h"

namespace Iceblur
{
	RenderingPipeline* Renderer::m_ActivePipeline;

	void Renderer::Initialize()
	{
		RenderingPipeline* pipeline = new RealisticRenderer();
		pipeline->Initialize();
		SetActiveRenderingPipeline(pipeline);

		EventSystem::Subscribe(WindowResizeEvent::type, &OnWindowResize);
	}

	void Renderer::SetActiveRenderingPipeline(RenderingPipeline* pipeline)
	{
		m_ActivePipeline = pipeline;
	}

	CameraComponent* Renderer::GetCurrentCamera()
	{
		if (SceneManager::GetCurrentScene()->GetCurrentCamera())
		{
			return const_cast<CameraComponent*>(SceneManager::GetCurrentScene()->GetCurrentCamera());
		}
		else if (GetCurrentPipeline()->GetSpectatorCamera())
		{
			return (CameraComponent*) GetCurrentPipeline()->GetSpectatorCamera();
		}
		else
		{
			return nullptr;
		}
	}

	void Renderer::Update(float deltaTime)
	{
		if (!m_ActivePipeline)
		{
			ICE_ERROR(Error::ETypes::NO_PIPELINE);
			return;
		}

		m_ActivePipeline->Update(deltaTime);
	}

	void Renderer::Shutdown()
	{
		if (m_ActivePipeline)
		{
			m_ActivePipeline->Shutdown();
		}

		ICE_INFO("Shutting down renderer...");
	}

	void Renderer::OnWindowResize(IceEventFn e)
	{
		m_ActivePipeline->Refresh();
	}
}
