// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Win64Window.h"

#include <GLFW/glfw3.h>

#include "Core/IO/Log.h"
#include "Event/EventSystem.h"

namespace Iceblur
{
    bool Win64Window::Create(const WindowProps& props)
    {
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
            ICE_ERROR("Failed to create window!");
            return false;
        }

        glfwMakeContextCurrent(m_Window);

        //Example callback for testing, more will be implemented soon
        glfwSetCursorPosCallback(m_Window, &MousePositionCallback);

        return true;
    }

    void Win64Window::MousePositionCallback(GLFWwindow* window, double x, double y)
    {
        MousePositionEvent event((float) x, (float) y);
        EventSystem::Dispatch(event);
    }
}
