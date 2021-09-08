// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Event/EventSystem.h"

namespace Iceblur
{
    Window* Application::m_Window = nullptr;

    int Application::Spawn()
    {
        OnInit();
        return 0;
    }

    void Application::OnInit()
    {
        Log::Init();
        EventSystem::Initialize();

        ICE_PRINTN("Welcome to Iceblur Engine! For more information, please visit https://github.com/Futureblur/IceblurEngine.");

        //TODO: GLFW error callback
        //TODO: Access window from a window manager class, not static instance

        auto window = new Window(EWindowType::EditorPopup);

        m_Window = window;

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            ICE_ERROR("Failed to initialize glad!");
        }

        OnPostInit();
    }

    void Application::OnPostInit()
    {
        while (!glfwWindowShouldClose(m_Window->GetGLFWWindow()))
        {
            OnUpdate();
        }

        OnShutdown();
    }

    void Application::OnUpdate()
    {
        glfwSwapBuffers(m_Window->GetGLFWWindow());
        glfwPollEvents();
    }

    void Application::OnShutdown()
    {
        glfwTerminate();
    }
}
