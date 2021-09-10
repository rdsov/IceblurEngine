// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "VMath.h"

#include "Core/IO/Log.h"

namespace Iceblur
{
    void Resolution::ResolutionNullError()
    {
        ICE_ERROR("Resolution width or height must be greater than zero!");
    }
}
