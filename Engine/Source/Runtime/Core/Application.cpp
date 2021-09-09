// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Platform/Windows/Win64Window.h"
#include "Event/EventSystem.h"

namespace Iceblur
{
    Win64Window* Application::m_Window = nullptr;

    int Application::Spawn()
    {
        OnInit();
        return 0;
    }

    void Application::OnInit()
    {
        Log::Init();
        EventSystem::Initialize();

        ICE_PRINT("Welcome to Iceblur Engine! For more information, please visit https://github.com/Futureblur/IceblurEngine.");

        //TODO: GLFW error callback
        //TODO: Access window from a window manager class, not static instance

        auto window = new Win64Window(EWindowType::EditorPopup);

        m_Window = window;

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            ICE_ERROR("Failed to initialize glad!");
        }

        OnPostInit();
    }

    void Application::OnPostInit()
    {
        while (!glfwWindowShouldClose((GLFWwindow*) m_Window->GetNativeWindow()))
        {
            OnUpdate();
        }

        OnShutdown();
    }

    void Application::OnUpdate()
    {
        glfwSwapBuffers((GLFWwindow*) m_Window->GetNativeWindow());
        glfwPollEvents();
    }

    void Application::OnShutdown()
    {
        glfwTerminate();
    }
}
