// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "../Core.h"

#ifdef ICE_WIN64

#include <Windows.h>

#endif

#undef near
#undef far

namespace Iceblur
{
    class ICE_API Log
    {
    public:
        static void Init();

        //Used for debugging purposes. Prints message only to host console.
        //All other logging functions will print the message to the editor console in the future.
        static void Print(std::string text);

        static void Message(std::string message);

        static void Info(std::string info);

        static void Warn(std::string warning);

        static void Error(std::string error);

    private:
        enum ConsoleColor : WORD
        {
            Blue = 3,
            Red = 12,
            Yellow = 14,
            White = 15
        };

        static void SetConsoleColor(ConsoleColor color);

        //Returns the current formatted time string.
        static std::string GetFormattedTime();

    private:
        static inline HANDLE m_ConsoleHandle;
    };
}

//TODO: Some macros may be changed in the future

#define ICE_PRINT(x) std::cout << x;                //Shorthand for std::cout
#define ICE_PRINTN(x) std::cout << x << std::endl   //Shorthand for std::cout, but with new line.
#define ICE_LOG(x) Log::Print(x)                    //Used for debugging only. Prints raw message with no formatting.
#define ICE_MESSAGE(x) Log::Message(x)              //Logs a simple message to the console. Color: White
#define ICE_INFO(x) Log::Info(x)                    //Logs info to the console. Color: Blue
#define ICE_WARN(x) Log::Warn(x)                    //Logs warning to the console. Color: Yellow
#define ICE_ERROR(x) Log::Error(x)                  //Logs error to the console. Color: Red
#define ICE_FATAL(x) Log::Error(x); return          //Logs error to the console and prevents code from continuing. Color: Red
