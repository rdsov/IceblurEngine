// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"
#include "Event/IEvent.h"

namespace Iceblur
{
	struct RenderingPipeline;

	class ICE_API Renderer
	{
	public:
		static void Initialize();

		static void SetActiveRenderingPipeline(RenderingPipeline* pipeline);

		static const RenderingPipeline* GetCurrentPipeline()
		{
			return m_ActivePipeline;
		}

		static void Update(float deltaTime);

		static void Shutdown();

	private:
		static void OnWindowResize(IceEventFn e);

	private:
		static RenderingPipeline* m_ActivePipeline;
	};
}
