// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core.h"
#include "Math/VMath.h"

namespace Iceblur
{
	//Sets the properties for a window.
	struct WindowProps
	{
		std::string Title = "Untitled Window";
		Resolution resolution = Resolution(1280, 720);
		int RefreshRate = 60;
		bool Maximized = true;
		bool Fullscreen = false;
		bool UseMonitorResolution = false;
		bool UseMonitorRefreshRate = false;
		bool enableVSync = false;
	};

	//Speeds up the process of creating a window.
	//This config enum overrides members of struct WindowProps
	//The window resolution can be overridden by setting
	//WindowProps.UseMonitorResolution = true
	enum class EWindowType
	{
		Unknown,
		Editor,
		EditorPopup,
		FullscreenGame
	};

	struct Window
	{
	public:
		Window() : m_Type(EWindowType::Unknown)
		{
		}

		virtual ~Window() = default;

		NODISCARD virtual void* GetNativeWindow() const = 0;

	protected:
		virtual bool Create(const WindowProps& props) = 0;

	protected:
		EWindowType m_Type;

		friend class WindowManager;
	};
}
