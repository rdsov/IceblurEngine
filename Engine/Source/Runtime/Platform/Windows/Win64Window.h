// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Window.h"

struct GLFWwindow;

namespace Iceblur
{
	struct RenderingAPIProps;

	class Win64Window : public Window
	{
	public:
		Win64Window(RenderingAPIProps* props) : m_APIProps(props)
		{
		}

		~Win64Window() override = default;

		NODISCARD void* GetNativeWindow() const override
		{
			return m_Window;
		}

		void Close() override;

		Resolution GetSize() const override;

		Resolution GetMousePosition() const;

	private:
		bool Create(const WindowProps& props) override;

		static void WindowMaximizeCallback(GLFWwindow* window, int maximized);

		static void WindowSizeCallback(GLFWwindow* window, int width, int height);

		static void WindowMoveCallback(GLFWwindow* window, int x, int y);

		static void MousePositionCallback(GLFWwindow* window, double x, double y);

		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	private:
		friend class WindowManager;

		GLFWwindow* m_Window = nullptr;

		RenderingAPIProps* m_APIProps;
	};
}
