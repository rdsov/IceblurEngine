// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"

#define ERR_ENUM_LENGTH_DOESNT_MATCH "Enum length doesn't match the array length!"

namespace Iceblur
{
    struct Error
    {
        enum class ETypes
        {
            NONE
        };

        enum EFailed
        {
            GLAD_INIT,
            GLFW_INIT,
            WINDOW_CREATION
        };

        NODISCARD static std::string GetFailedString(EFailed error);
    };
}
