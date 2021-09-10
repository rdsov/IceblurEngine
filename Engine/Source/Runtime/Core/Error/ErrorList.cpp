// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "ErrorList.h"

namespace Iceblur
{
    static std::string FailedTypes[] =
            {
                    "Failed to initialize GLAD!",
                    "Failed to initialize GLFW!",
                    "Failed to create window!"
            };

    static_assert(sizeof(FailedTypes) / Error::EFailed::WINDOW_CREATION != 1, ERR_ENUM_LENGTH_DOESNT_MATCH);

    std::string Iceblur::Error::GetFailedString(Iceblur::Error::EFailed error)
    {
        return FailedTypes[error];
    }
}
