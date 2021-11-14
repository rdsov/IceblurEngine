// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Log.h"

#include "Core/VTime.h"
#include "Platform/PlatformDetection.h"

#ifdef ICE_WIN64

#include <Windows.h>

#endif

#undef near
#undef far

#include "Core/CoreUtils.h"

namespace Iceblur
{
	void Log::Init()
	{
		m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		ResetConsoleColor();
	}

	void Log::Print(IceString text)
	{
		if (!CheckVerbosity(ELogVerbosity::Debug)) return;

		SetConsoleColor(EConsoleColor::White);
		ICE_PRINT(text);
		ResetConsoleColor();
	}

	void Log::Message(IceString message)
	{
		if (!CheckVerbosity(ELogVerbosity::Info)) return;

		SetConsoleColor(EConsoleColor::White);
		std::string out = GetFormattedTime() + " " + message;
		ICE_PRINT(out);
		ResetConsoleColor();
	}

	void Log::Info(IceString info)
	{
		if (!CheckVerbosity(ELogVerbosity::Info)) return;

		SetConsoleColor(EConsoleColor::Blue);
		std::string out = GetFormattedTime() + " [INFO] " + info;
		ICE_PRINT(out);
		ResetConsoleColor();
	}

	void Log::Warn(Error::ETypes error, const Error::ErrorArgs& args)
	{
		if (!CheckVerbosity(ELogVerbosity::Warning)) return;

		std::string warning;
		warning = Error::ToString(error, args);
		Warn(warning);
	}

	void Log::Warn(Error::EFailed error, const Error::ErrorArgs& args)
	{
		if (!CheckVerbosity(ELogVerbosity::Warning)) return;

		std::string warning;
		warning = Error::ToString(error, args);
		Warn(warning);
	}

	void Log::Warn(IceString warning)
	{
		if (!CheckVerbosity(ELogVerbosity::Warning)) return;

		SetConsoleColor(EConsoleColor::Yellow);
		std::string out = GetFormattedTime() + " [WARNING] " + warning;
		ICE_PRINT(out);
		ResetConsoleColor();
	}

	void Log::Error(Error::ETypes error, const Error::ErrorArgs& args)
	{
		if (!CheckVerbosity(ELogVerbosity::Error)) return;

		std::string err;
		err = Error::ToString(error, args);
		Error(err);
	}

	void Log::Error(Error::EFailed error, const Error::ErrorArgs& args)
	{
		if (!CheckVerbosity(ELogVerbosity::Error)) return;

		std::string err;
		err = Error::ToString(error, args);
		Error(err);
	}

	void Log::Error(IceString error)
	{
		if (!CheckVerbosity(ELogVerbosity::Error)) return;

		SetConsoleColor(EConsoleColor::Red);
		std::string out = GetFormattedTime() + " [ERROR] " + error;
		ICE_PRINT(out);
		ResetConsoleColor();
	}

	void Log::SetConsoleColor(EConsoleColor color)
	{
		SetConsoleTextAttribute(m_ConsoleHandle, color);
	}

	void Log::ResetConsoleColor()
	{
		SetConsoleColor(EConsoleColor::White);
	}

	std::string Log::GetFormattedTime()
	{
		TimeData now = VTime::GetTimeNow();

		std::string formattedTime = "[" + TimeData::ToString(now.Hours) + ":"
		                            + TimeData::ToString(now.Minutes) + ":"
		                            + TimeData::ToString(now.Seconds) + "]";
		return formattedTime;
	}

	bool Log::CheckVerbosity(uint8_t level)
	{
		return m_LogVerbosity >= level;
	}
}
