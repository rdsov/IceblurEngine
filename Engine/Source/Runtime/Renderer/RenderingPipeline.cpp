// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "RenderingPipeline.h"

#include <glad/glad.h>

#include "Core/IO/Log.h"

namespace Iceblur
{
    void BaseRenderer::Initialize()
    {
        m_ClearColor = Color();
    }

    void BaseRenderer::Update(double deltaTime)
    {
        ClearColor();
    }

    void BaseRenderer::ClearColor()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(ALL_COLOR_CHANNELS(m_ClearColor));
    }

    void BaseRenderer::Shutdown()
    {
        ICE_INFO("Shutting down 2D renderer...");
    }
}
