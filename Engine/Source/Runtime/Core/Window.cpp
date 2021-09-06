// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Window.h"

#include <GLFW/glfw3.h>

#include "IO/Log.h"

namespace Iceblur
{
    Window::Window(const WindowProps& props)
            : m_Window(nullptr), m_Type(EWindowType::Unknown)
    {
        Create(props);
    }

    Window::Window(const EWindowType& type, const WindowProps& props)
            : m_Window(nullptr), m_Type(type)
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
        }

        Create(configProps);
    }

    void Window::Create(const WindowProps& props)
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
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        glfwWindowHint(GLFW_MAXIMIZED, props.Maximized);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

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
    }
}
