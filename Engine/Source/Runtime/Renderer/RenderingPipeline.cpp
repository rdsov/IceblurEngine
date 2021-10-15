// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "RenderingPipeline.h"

#include <glad/glad.h>

#include "Core/IO/Log.h"

namespace Iceblur
{
    void SimpleRenderer::Initialize()
    {
        m_ClearColor = Color();
    }

    void SimpleRenderer::Update(double deltaTime)
    {
        ClearColor();
    }

    void SimpleRenderer::ClearColor()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(ALL_COLOR_CHANNELS(m_ClearColor));
    }

    void SimpleRenderer::Shutdown()
    {
        ICE_INFO("Shutting down 2D renderer...");
    }
}
