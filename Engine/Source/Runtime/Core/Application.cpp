// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/IO/VIO.h"

#include "WindowManager.h"
#include "Event/EventSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderingPipeline.h"

#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Scene/Entity.h"

#include "Scene/Components/TransformComponent.h"
#include "Scene/Components/MeshComponent.h"

namespace Iceblur
{
	Application* Application::m_Instance = nullptr;

	int Application::Spawn()
	{
		OnInit();
		return 0;
	}

	float Application::GetDeltaTime()
	{
		return glfwGetTime();
	}

	void Application::ForceUpdate()
	{
		OnUpdate(GetDeltaTime());
	}

	void Application::OnInit()
	{
		Log::Init();
		VIO::Init();
		EventSystem::Initialize();

		auto apiProps = new RenderingAPIProps("OpenGL", 4, 6);

		WindowManager::Initialize(apiProps);

		ICE_PRINT("Welcome to Iceblur Engine! For more information, please visit https://github.com/Futureblur/IceblurEngine");

		//TODO: GLFW error callback
		OnPostInit();
	}

	void Application::OnPostInit()
	{
		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		{
			ICE_ERROR(Error::EFailed::GLAD_INIT);
		}

		Renderer::Initialize();

		SceneProps props;
		props.name = "Dev Scene";

		auto devScene = SceneManager::CreateNew(props);
		SceneManager::LoadScene(devScene);

		OnStart();

		while (WindowManager::IsWindowRunning(WindowManager::GetHost()))
		{
			OnUpdate(GetDeltaTime());
		}

		OnShutdown();
	}

	void Application::OnStart()
	{
		auto ent = Entity::CreateAndAdd("Awesome Entity");
		Entity::CreateAndAdd("Cool Entity");
		Entity::CreateAndAdd("Great Entity");

		//ent->GetComponent<TransformComponent>()->SetPosition(glm::vec3(0, 69, 0));

		std::vector<Vertex> m_Vertices = {
				Vertex(0.5f, 0.5f, 0.0f, 1.0f, 1.0f),
				Vertex(0.5f, -0.5f, 0.0f, 1.0f, 0.0f),
				Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f),
				Vertex(-0.5f, 0.5f, 0.0f, 0.0f, 1.0f)
		};

		std::vector<VID> m_Indices = {
				0, 1, 3,   // first triangle
				1, 2, 3    // second triangle
		};

		MeshData* data = new MeshData(m_Vertices, m_Indices);
		ent->AddComponent<MeshComponent>(new MeshComponent(data));
	}

	void Application::OnUpdate(float deltaTime)
	{
		Renderer::Update(deltaTime);
		WindowManager::UpdateWindow(WindowManager::GetHost());
	}

	void Application::OnShutdown()
	{
		Renderer::Shutdown();
		glfwTerminate();
	}
}
