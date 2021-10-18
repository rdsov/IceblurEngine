// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "RenderingPipeline.h"

#include <glad/glad.h>

#include "Intern/OpenGLData.h"
#include "Shader.h"

#include "Core/IO/Log.h"
#include "Core/IO/VIO.h"

namespace Iceblur
{
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

		delete m_VertexShader;
		delete m_FragmentShader;

		//For testing purposes

		std::vector<Vertex> m_Vertices = {
				Vertex(0.5f, 0.5f, 0.0f, 1.0f, 1.0f),
				Vertex(0.5f, -0.5f, 0.0f, 1.0f, 0.0f),
				Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f),
				Vertex(-0.5f, 0.5f, 0.0f, 0.0f, 1.0f)
		};

		std::vector<uint32_t> m_Indices = {
				0, 1, 3,   // first triangle
				1, 2, 3    // second triangle
		};

		m_VAO = new VertexArrayObject();
		m_VAO->Generate();

		m_VBO = new VertexBuffer(m_Vertices.size() * sizeof(Vertex), &m_Vertices[0]);
		m_VBO->Generate();

		m_EBO = new ElementArrayBuffer(m_Indices.size() * sizeof(uint32_t), &m_Indices[0]);
		m_EBO->Generate();

		m_VAO->Bind();
		m_VBO->Bind();
		m_VBO->CopyToCurrent();

		m_EBO->Bind();
		m_EBO->CopyToCurrent();

		m_VAO->AttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*) nullptr);
		m_VAO->EnableAttribArray(0);

		m_VAO->AttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, uvs));
		m_VAO->EnableAttribArray(1);

		m_VBO->Unbind();
		m_VAO->Unbind();
	}

	void BaseRenderer::Update(double deltaTime)
	{
		ClearColor();

		//For testing purposes
		if (m_VAO)
		{
			m_VAO->Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}

	void BaseRenderer::ClearColor()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(ALL_COLOR_CHANNELS(m_ClearColor));
	}

	void BaseRenderer::Shutdown()
	{
		delete m_ShaderProgram;

		if (m_VBO)
		{
			m_VBO->Delete();
			delete m_VBO;
		}

		if (m_EBO)
		{
			m_EBO->Delete();
			delete m_EBO;
		}

		ICE_PRINT("Shutting down 2D renderer...");
	}
}
