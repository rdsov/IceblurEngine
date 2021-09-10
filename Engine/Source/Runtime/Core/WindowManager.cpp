// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "WindowManager.h"

#include <GLFW/glfw3.h>

#include "IO/Log.h"
#include "Platform/PlatformDetection.h"
#include "Platform/Windows/Win64Window.h"

namespace Iceblur
{
    void WindowManager::Initialize()
    {
#ifdef ICE_WIN64
        if (!glfwInit())
        {
            ICE_ERROR("Failed to initialize GLFW!");
        }
#else
#error "Platform is not supported!"
#endif
    }

    Window* WindowManager::CreateWindow(const EWindowType& type, const WindowProps& props, bool host)
    {
        WindowProps configProps;

        switch (type)
        {
            case EWindowType::Editor:
                configProps.Title = "Iceblur Editor";
                configProps.Maximized = true;
                configProps.Fullscreen = false;
                break;
            case EWindowType::EditorPopup:
                configProps.Title = "Iceblur Editor - Popup";
                configProps.Maximized = false;
                configProps.Fullscreen = false;
                break;
            case EWindowType::FullscreenGame:
                configProps.Title = "Made with Iceblur Engine";
                configProps.Maximized = true;
                configProps.Fullscreen = true;
                configProps.UseMonitorResolution = true;
                break;
            case EWindowType::Unknown:
                ICE_WARN("Unknown window type!");
                break;
        }

        WindowFnSignature signature;

        signature.type = type;
        signature.props = configProps;
        signature.isHost = host;

#ifdef ICE_WIN64
        return CreateWin64Window(signature);
#else
#error "Platform is not supported!";
#endif

        return nullptr;
    }

    Window* WindowManager::CreateWin64Window(const WindowFnSignature& signature)
    {
        auto window = new Win64Window();
        bool success = window->Create(signature.props);

        if (!success)
        {
            ICE_ERROR("Failed to create window!");
            return nullptr;
        }

        window->m_Type = signature.type;

        if (signature.isHost)
        {
            m_Host = window;
        }

        return window;
    }

    bool WindowManager::IsWindowRunning(Window* window)
    {
#ifdef ICE_WIN64
        return IsWin64WindowRunning(window);
#else
#error "Platform is not supported!";
#endif
    }

    void WindowManager::UpdateWindow(Window* window)
    {
#ifdef ICE_WIN64
        UpdateWin64Window(window);
#else
#error "Platform is not supported!";
#endif
    }

    bool WindowManager::IsWin64WindowRunning(Window* window)
    {
        bool running = !glfwWindowShouldClose((GLFWwindow*) window->GetNativeWindow());

        return running;
    }

    void WindowManager::UpdateWin64Window(Window* window)
    {
        glfwSwapBuffers((GLFWwindow*) window->GetNativeWindow());
        glfwPollEvents();
    }
}
