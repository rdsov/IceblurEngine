// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "RenderingPipeline.h"

#include "Core/IO/Log.h"

namespace Iceblur
{
    void SimpleRenderer::Initialize()
    {
        ICE_INFO("Initialized 2D renderer.");
    }

    void SimpleRenderer::Update(double deltaTime)
    {
        //ICE_PRINT(deltaTime);
    }

    void SimpleRenderer::Shutdown()
    {
        ICE_INFO("Shutting down 2D renderer...");
    }
}
