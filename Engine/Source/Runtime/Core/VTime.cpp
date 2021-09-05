// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "VTime.h"

#include "IO/Log.h"

#define _CRT_SECURE_NO_WARNINGS

namespace Iceblur
{
    TimeData VTime::GetTimeNow()
    {
        std::time_t time = std::time(nullptr);
        std::tm* timeNow = std::localtime(&time);

        TimeData data{};
        data.Hours = timeNow->tm_hour;
        data.Minutes = timeNow->tm_min;
        data.Seconds = timeNow->tm_sec;

        return data;
    }
}
