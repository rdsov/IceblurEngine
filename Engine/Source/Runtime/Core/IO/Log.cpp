// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Log.h"
#include "../VTime.h"

namespace Iceblur
{
    void Log::Init()
    {
        m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleColor(ConsoleColor::White);
    }

    void Log::Print(std::string text)
    {
        SetConsoleColor(ConsoleColor::White);
        ICE_PRINTN(text);
    }

    void Log::Message(std::string message)
    {
        SetConsoleColor(ConsoleColor::White);
        std::string out = GetFormattedTime() + " " + message;
        ICE_PRINTN(out);
    }

    void Log::Info(std::string info)
    {
        SetConsoleColor(ConsoleColor::Blue);
        std::string out = GetFormattedTime() + " [INFO] " + info;
        ICE_PRINTN(out);
    }

    void Log::Warn(std::string warning)
    {
        SetConsoleColor(ConsoleColor::Yellow);
        std::string out = GetFormattedTime() + " [WARNING] " + warning;
        ICE_PRINTN(out);
    }

    void Log::Error(std::string error)
    {
        SetConsoleColor(ConsoleColor::Red);
        std::string out = GetFormattedTime() + " [ERROR] " + error;
        ICE_PRINTN(out);
    }

    void Log::SetConsoleColor(ConsoleColor color)
    {
        SetConsoleTextAttribute(m_ConsoleHandle, color);
    }

    std::string Log::GetFormattedTime()
    {
        TimeData now = VTime::GetTimeNow();
        std::string formattedTime = "[" + ICE_TOS(now.Hours) + ":" + ICE_TOS(now.Minutes) + ":" + ICE_TOS(now.Seconds) + "]";
        return formattedTime;
    }
}
