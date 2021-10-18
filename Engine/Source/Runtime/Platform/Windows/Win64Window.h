// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Window.h"

struct GLFWwindow;

namespace Iceblur
{
	class Win64Window : public Window
	{
	public:
		Win64Window() = default;

		~Win64Window() override = default;

		NODISCARD void* GetNativeWindow() const override
		{
			return m_Window;
		}

	private:
		bool Create(const WindowProps& props) override;

		static void WindowMaximizeCallback(GLFWwindow* window, int maximized);

		static void WindowSizeCallback(GLFWwindow* window, int width, int height);

		static void MousePositionCallback(GLFWwindow* window, double x, double y);

	private:
		friend class WindowManager;

		GLFWwindow* m_Window = nullptr;
	};
}
