// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Win64Window.h"

#include <GLFW/glfw3.h>

#include "Core/IO/Log.h"
#include "Core/WindowManager.h"
#include "Core/Application.h"

#include "Event/EventSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderingPipeline.h"

namespace Iceblur
{
	void Win64Window::Close()
	{
		glfwSetWindowShouldClose(m_Window, true);
	}

	Resolution Win64Window::GetSize() const
	{
		int width, height;
		glfwGetWindowSize(m_Window, &width, &height);
		return Resolution(width, height);
	}

	Resolution Win64Window::GetMousePosition() const
	{
		double x, y;
		glfwGetCursorPos(m_Window, &x, &y);
		return Resolution(x, y);
	}

	bool Win64Window::Create(const WindowProps& props)
	{
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		//GLFW window hints

		if (!m_APIProps)
		{
			ICE_ERROR(Error::ETypes::A_NULLPTR, { "RenderingAPIProps" });
			return false;
		}

		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);

		glfwWindowHint(GLFW_MAXIMIZED, props.maximized);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_APIProps->versionMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_APIProps->versionMinor);

		if (m_APIProps->name == "OpenGL")
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}

		//Set window properties

		GLFWmonitor* monitor = nullptr;

		if (props.fullscreen)
		{
			monitor = glfwGetPrimaryMonitor();
		}

		int refreshRate = props.refreshRate;
		if (props.useMonitorRefreshRate)
		{
			refreshRate = mode->refreshRate;
		}

		glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);

		int width = props.resolution.GetWidth();
		int height = props.resolution.GetHeight();

		if (props.useMonitorResolution)
		{
			width = mode->width;
			height = mode->height;
		}

		m_Window = glfwCreateWindow(width, height, props.title.c_str(), monitor, nullptr);

		if (!m_Window)
		{
			ICE_ERROR(Error::EFailed::WINDOW_CREATION);
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(m_Window);

		//Should we enable VSync?
		glfwSwapInterval(!props.enableVSync);

		glfwSetWindowMaximizeCallback(m_Window, &WindowMaximizeCallback);
		glfwSetWindowSizeCallback(m_Window, &WindowSizeCallback);
		glfwSetWindowPosCallback(m_Window, &WindowMoveCallback);
		glfwSetCursorPosCallback(m_Window, &MousePositionCallback);
		glfwSetKeyCallback(m_Window, &KeyCallback);
		glfwSetMouseButtonCallback(m_Window, &MouseButtonCallback);
		glfwSetScrollCallback(m_Window, &ScrollCallback);

		return true;
	}

	void Win64Window::WindowMaximizeCallback(GLFWwindow* window, int maximized)
	{
		WindowMaximizeEvent event(WindowManager::GetStaticWindow(window), maximized);
		EventSystem::Dispatch(event);
	}

	void Win64Window::WindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		/* When we resize the window, we want to re-render everything to the screen.
		 * Note that we should not call Application::OnUpdate() as this also calls
		 * other functions that are not relevant for rendering.
		 * One other problem is that Application::OnUpdate also calls
		 * glfwSwapBuffers(), which is quite laggy currently.
		 *
		 * Update (10/25/2021)
		 * Somehow it doesn't seem to lag anymore. And I don't know why. Interesting.
		*/

		Application::GetInstance()->ForceUpdate();
		//Renderer::Update(Application::GetInstance()->GetDeltaTime());

		WindowResizeEvent event(WindowManager::GetStaticWindow(window), width, height);
		EventSystem::Dispatch(event);
	}

	void Win64Window::WindowMoveCallback(GLFWwindow* window, int x, int y)
	{
		Application::GetInstance()->ForceUpdate();

		WindowMoveEvent event(WindowManager::GetStaticWindow(window), x, y);
		EventSystem::Dispatch(event);
	}

	void Win64Window::MousePositionCallback(GLFWwindow* window, double x, double y)
	{
		MouseMoveEvent event((float) x, (float) y);
		EventSystem::Dispatch(event);
	}

	void Win64Window::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		MouseScrollEvent event(xOffset, yOffset);
		EventSystem::Dispatch(event);
	}

	void Win64Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		MouseButtonEvent event(button, action);
		EventSystem::Dispatch(event);
	}

	void Win64Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		KeyEvent event(key, action, scancode);
		EventSystem::Dispatch(event);
	}
}
