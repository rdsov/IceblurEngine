// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Log.h"

#include "Core/VTime.h"
#include "Platform/PlatformDetection.h"

#ifdef ICE_WIN64

#include <Windows.h>

#endif

#undef near
#undef far

namespace Iceblur
{
    void Log::Init()
    {
        m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        ResetConsoleColor();
    }

    void Log::Print(const std::string& text)
    {
        SetConsoleColor(EConsoleColor::White);
        ICE_PRINT(text);
        ResetConsoleColor();
    }

    void Log::Message(const std::string& message)
    {
        SetConsoleColor(EConsoleColor::White);
        std::string out = GetFormattedTime() + " " + message;
        ICE_PRINT(out);
        ResetConsoleColor();
    }

    void Log::Info(const std::string& info)
    {
        SetConsoleColor(EConsoleColor::Blue);
        std::string out = GetFormattedTime() + " [INFO] " + info;
        ICE_PRINT(out);
        ResetConsoleColor();
    }

    void Log::Warn(Error::ETypes error, const Error::ErrorArgs& args)
    {
        std::string warning;

        warning = Error::ToString(error, args);

        Warn(warning);
    }

    void Log::Warn(Error::EFailed error, const Error::ErrorArgs& args)
    {
        std::string warning;

        warning = Error::ToString(error, args);

        Warn(warning);
    }

    void Log::Warn(const std::string& warning)
    {
        SetConsoleColor(EConsoleColor::Yellow);
        std::string out = GetFormattedTime() + " [WARNING] " + warning;
        ICE_PRINT(out);
        ResetConsoleColor();
    }

    void Log::Error(Error::ETypes error, const Error::ErrorArgs& args)
    {
        std::string err;

        err = Error::ToString(error, args);

        Error(err);
    }

    void Log::Error(Error::EFailed error, const Error::ErrorArgs& args)
    {
        std::string err;

        err = Error::ToString(error, args);

        Error(err);
    }

    void Log::Error(const std::string& error)
    {
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
}
