// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"
#include "Core/Error/ErrorList.h"
#include "Core/CoreUtils.h"

#define _CRT_SECURE_NO_WARNINGS

typedef void* HANDLE;
typedef unsigned short WORD;

namespace Iceblur
{
	class ICE_API Log
	{
	public:
		static void Init();

		//Used for debugging purposes. Prints message only to host console.
		//All other logging functions will print the message to the editor console in the future.
		static void Print(IceString text);

		static void Message(IceString message);

		static void Info(IceString info);

		static void Warn(Error::ETypes error, const Error::ErrorArgs& args = { });

		static void Warn(Error::EFailed error, const Error::ErrorArgs& args = { });

		static void Warn(IceString warning);

		static void Error(Error::ETypes error, const Error::ErrorArgs& args = { });

		static void Error(Error::EFailed error, const Error::ErrorArgs& args = { });

		static void Error(IceString error);

	private:
		enum EConsoleColor : WORD
		{
			Blue = 3,
			Red = 12,
			Yellow = 14,
			White = 15
		};

		static void SetConsoleColor(EConsoleColor color);

		//Returns the current formatted time string.
		static std::string GetFormattedTime();

	private:
		static void ResetConsoleColor();

	private:
		static inline HANDLE m_ConsoleHandle;
	};
}

//Fixme: Some macros may be changed in the future

#define ICE_PRINT(x) std::cout << x << std::endl        //Shorthand for std::cout, but with new line.

#ifdef ICE_DEBUG
#define ICE_LOG(x) Log::Print(x)                        //Used for debugging only. Prints raw message to console with no formatting.
#else
#define ICE_LOG(x)
#endif

#define ICE_MESSAGE(x) Log::Message(x)                  //Logs a simple message to the console. Color: White
#define ICE_INFO(x) Log::Info(x)                        //Logs info to the console. Color: Blue
#define ICE_WARN(...) Log::Warn(__VA_ARGS__)            //Logs warning to the console. Color: Yellow
#define ICE_ERROR(...) Log::Error(__VA_ARGS__)          //Logs error to the console. Color: Red
#define ICE_FATAL(...) Log::Error(__VA_ARGS__); return  //Logs error to the console and prevents code from continuing. Color: Red
