// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "VMath.h"

#include "Core/IO/Log.h"

namespace Iceblur
{
    void Resolution::ResolutionNullError()
    {
        ICE_ERROR(Error::ETypes::AMUST_BE_GREATER_THAN_ZERO, { "Resolution width or height" });
    }
}
