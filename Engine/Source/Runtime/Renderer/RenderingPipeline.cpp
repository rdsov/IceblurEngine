// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "RenderingPipeline.h"

#include <glad/glad.h>

#include "Core/IO/Log.h"
#include "Core/IO/IoManager.h"

namespace Iceblur
{
    void BaseRenderer::Initialize()
    {
        m_ClearColor = Color();

        m_VertexShader = new Shader(GL_VERTEX_SHADER, IOManager::GetEngineLocation() + "\\Shaders\\VertexShader.glsl");
        m_FragmentShader = new Shader(GL_FRAGMENT_SHADER, IOManager::GetEngineLocation() + "\\Shaders\\FragmentShader.glsl");

        m_ShaderProgram = new ShaderProgram();
        m_ShaderProgram->Attach(m_VertexShader);
        m_ShaderProgram->Attach(m_FragmentShader);
        m_ShaderProgram->Link();
        m_ShaderProgram->Use();
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
