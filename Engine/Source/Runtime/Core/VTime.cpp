// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "VTime.h"

#include "IO/Log.h"

#include <GLFW/glfw3.h>

#define _CRT_SECURE_NO_WARNINGS

namespace Iceblur
{
	float VTime::m_CurrentTick;
	float VTime::m_LastTick;
	float VTime::m_Accumulated;
	float VTime::m_LastFrameTime;
	float VTime::m_FPS;
	float VTime::m_DeltaTime;

	TimeData VTime::GetTimeNow()
	{
		std::time_t time = std::time(nullptr);
		std::tm* timeNow = std::localtime(&time);

		TimeData data { };
		data.Hours = timeNow->tm_hour;
		data.Minutes = timeNow->tm_min;
		data.Seconds = timeNow->tm_sec;

		return data;
	}

	void VTime::Update()
	{
		m_CurrentTick = (float) glfwGetTime();
		m_DeltaTime = m_CurrentTick - m_LastFrameTime;
		m_LastFrameTime = m_CurrentTick;

		m_Accumulated++;
		if (m_CurrentTick - m_LastTick >= 1.0f)
		{
			m_FPS = m_Accumulated;
			m_Accumulated = 0.0f;
			m_LastTick = m_CurrentTick;
			//m_FrameTime = ImGui::GetIO().DeltaTime * 1000.0f;
		}
	}
}
