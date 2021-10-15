// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Renderer.h"

#include <GLFW/glfw3.h>

#include "RenderingPipeline.h"
#include "Core/IO/Log.h"

namespace Iceblur
{
    RenderingPipeline* Renderer::m_ActivePipeline;

    void Renderer::Initialize()
    {
        RenderingPipeline* pipeline = new BaseRenderer();

        pipeline->Initialize();
        SetActiveRenderingPipeline(pipeline);
    }

    void Renderer::SetActiveRenderingPipeline(RenderingPipeline* pipeline)
    {
        m_ActivePipeline = pipeline;
    }

    void Renderer::Update()
    {
        if (!m_ActivePipeline)
        {
            ICE_ERROR(Error::ETypes::NO_PIPELINE);
            return;
        }

        m_ActivePipeline->Update(glfwGetTime());
    }

    void Renderer::Shutdown()
    {
        if (m_ActivePipeline)
        {
            m_ActivePipeline->Shutdown();
        }

        ICE_LOG("Shutting down renderer...");
    }
}
