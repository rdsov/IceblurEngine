// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"

namespace Iceblur
{
	struct TimeData
	{
		int Hours;
		int Minutes;
		int Seconds;

		NODISCARD static inline std::string ToString(int value)
		{
			std::string time = ICE_TOS(value);

			if (value <= 9)
			{
				time = "0" + time;
			}

			return time;
		}
	};

	class VTime
	{
	public:
		static TimeData GetTimeNow();

		static const float GetDeltaTime()
		{
			return m_DeltaTime;
		}

		static const float GetFPS()
		{
			return m_FPS;
		}

		static void Update();

	private:
		static float m_CurrentTick;
		static float m_LastTick;
		static float m_Accumulated;
		static float m_LastFrameTime;
		static float m_FPS;
		static float m_DeltaTime;
	};
}
