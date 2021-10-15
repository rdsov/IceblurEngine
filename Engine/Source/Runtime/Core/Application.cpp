// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowManager.h"
#include "Event/EventSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderingPipeline.h"

namespace Iceblur
{
    int Application::Spawn()
    {
        OnInit();
        return 0;
    }

    void Application::OnInit()
    {
        Log::Init();
        EventSystem::Initialize();
        WindowManager::Initialize();
        Renderer::Initialize();

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
