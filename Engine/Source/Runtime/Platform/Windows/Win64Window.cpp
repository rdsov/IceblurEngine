// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Win64Window.h"

#include <GLFW/glfw3.h>

#include "Core/IO/Log.h"
#include "Event/EventSystem.h"

namespace Iceblur
{
    Win64Window::Win64Window(const EWindowType& type, const WindowProps& props)
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

        Win64Window::Create(configProps);
    }

    void Win64Window::Create(const WindowProps& props)
    {
        if (!glfwInit())
        {
            ICE_FATAL("Failed to initialize GLFW!");
        }

        //TODO: Create Graphics API struct for storing GLFW_CONTEXT_VERSION_X for example.

        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, props.RefreshRate);

        glfwWindowHint(GLFW_MAXIMIZED, props.Maximized);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        GLFWmonitor* monitor = nullptr;

        if (props.Fullscreen)
        {
            monitor = glfwGetPrimaryMonitor();
        }

        int width = props.Width;
        int height = props.Height;

        if (props.UseMonitorResolution)
        {
            width = mode->width;
            height = mode->height;
        }

        m_Window = glfwCreateWindow(width, height, props.Title.c_str(), monitor, nullptr);

        if (!m_Window)
        {
            glfwTerminate();
            ICE_FATAL("Failed to create window!");
        }

        glfwMakeContextCurrent(m_Window);

        //Example callback for testing, more will be implemented soon
        glfwSetCursorPosCallback(m_Window, &MousePositionCallback);
    }

    void Win64Window::MousePositionCallback(GLFWwindow* window, double x, double y)
    {
        MousePositionEvent event((float) x, (float) y);
        EventSystem::Dispatch(event);
    }
}
