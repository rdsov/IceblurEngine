// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowManager.h"
#include "Event/EventSystem.h"

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

        ICE_PRINT("Welcome to Iceblur Engine! For more information, please visit https://github.com/Futureblur/IceblurEngine.");

        //TODO: GLFW error callback

        WindowManager::CreateWindow(EWindowType::EditorPopup, {}, true);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            ICE_ERROR("Failed to initialize glad!");
        }

        OnPostInit();
    }

    void Application::OnPostInit()
    {
        while (WindowManager::IsWindowRunning(WindowManager::GetHost()))
        {
            OnUpdate();
        }

        OnShutdown();
    }

    void Application::OnUpdate()
    {
        WindowManager::UpdateWindow(WindowManager::GetHost());
    }

    void Application::OnShutdown()
    {
        glfwTerminate();
    }
}
