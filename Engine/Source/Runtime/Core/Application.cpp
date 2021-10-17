// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowManager.h"
#include "Event/EventSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderingPipeline.h"
#include "Core/IO/VIO.h"

namespace Iceblur
{
	Application* Application::m_Instance = nullptr;

	int Application::Spawn()
	{
		OnInit();
		return 0;
	}

	void Application::OnInit()
	{
		Log::Init();
		VIO::Init();
		EventSystem::Initialize();
		WindowManager::Initialize();

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

		while (WindowManager::IsWindowRunning(WindowManager::GetHost()))
		{
			OnUpdate();
		}

		OnShutdown();
	}

	void Application::OnUpdate()
	{
		Renderer::Update();
		WindowManager::UpdateWindow(WindowManager::GetHost());
	}

	void Application::OnShutdown()
	{
		Renderer::Shutdown();
		glfwTerminate();
	}
}
