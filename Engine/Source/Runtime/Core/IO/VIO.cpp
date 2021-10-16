// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "VIO.h"

#include "Log.h"

namespace Iceblur
{
    void VIO::Init()
    {
        if (Empty(GetEngineLocation()))
        {
            ICE_FATAL(Error::ETypes::A_NOT_FOUND, { "/InstallLocation.txt" });
            return;
        }
    }
}
