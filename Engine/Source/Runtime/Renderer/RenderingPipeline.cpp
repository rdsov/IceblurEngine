// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "RenderingPipeline.h"

#include <glad/glad.h>

#include "Core/IO/Log.h"
#include "Core/IO/VIO.h"

namespace Iceblur
{
    uint32_t m_VAO;
    uint32_t m_VBO;
    uint32_t m_EBO;

    void BaseRenderer::Initialize()
    {
        m_ClearColor = Color();

        m_VertexShader = new Shader(GL_VERTEX_SHADER, VIO::GetEngineLocation() + "\\Shaders\\UnlitVertexShader.glsl");
        m_FragmentShader = new Shader(GL_FRAGMENT_SHADER, VIO::GetEngineLocation() + "\\Shaders\\UnlitFragmentShader.glsl");

        m_ShaderProgram = new ShaderProgram();
        m_ShaderProgram->Attach(m_VertexShader);
        m_ShaderProgram->Attach(m_FragmentShader);
        m_ShaderProgram->Link();
        m_ShaderProgram->Use();

        //For testing purposes
        std::vector<float> m_Vertices = {
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // top right
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f  // top left
        };

        std::vector<uint32_t> m_Indices = {
                0, 1, 3,   // first triangle
                1, 2, 3    // second triangle
        };

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float), &m_Vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void BaseRenderer::Update(double deltaTime)
    {
        ClearColor();

        //For testing purposes
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
