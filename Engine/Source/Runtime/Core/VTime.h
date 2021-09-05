// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

namespace Iceblur
{
    struct TimeData
    {
        int Hours;
        int Minutes;
        int Seconds;
    };

    class VTime
    {
    public:
        static TimeData GetTimeNow();
    };
}
