// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core.h"
#include "IO/Log.h"

namespace Iceblur
{
	class ICE_API Application
	{
	public:
		Application()
		{
			ICE_SINGLETON(m_Instance, Application)
		}

		virtual ~Application() = default;

		//Spawns the host window. This currently returns 0, but this will change in the future.
		virtual int Spawn();

	public:
		static Application* GetInstance()
		{
			return m_Instance;
		}

		//Calls OnUpdate() function
		virtual void ForceUpdate();

	protected:
		virtual void OnInit();

		//Initialize here
		virtual void OnPostInit();

		//Create game relevant objects here
		virtual void OnStart();

		virtual void OnUpdate(float deltaTime);

		virtual void OnShutdown();

	private:
		static Application* m_Instance;
	};
}
