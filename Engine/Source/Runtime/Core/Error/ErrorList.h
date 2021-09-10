// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"

namespace Iceblur
{
    struct ICE_API Error
    {
        //Generic error types
        enum class ETypes
        {
            NONE,
            SINGLETON,
            LAST
        };

        enum class EFailed
        {
            GLAD_INIT,
            GLFW_INIT,
            WINDOW_CREATION,
            CAST_EVENT,
            LAST
        };

        //Returns full error string of ETypes enum
        NODISCARD static std::string ToString(ETypes error, const std::string args[] = { });

        //Returns full error string of EFailed enum
        NODISCARD static std::string ToString(EFailed error, const std::string args[] = { });
    };
}
