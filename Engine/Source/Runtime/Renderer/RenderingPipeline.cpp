// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "RenderingPipeline.h"

#include "Intern/OpenGLData.h"
#include "Shader.h"

#include <glad/glad.h>

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

		//glGenVertexArrays(1, &m_VAO);
		m_VAO = new VertexArrayObject();
		m_VAO->Generate();

		m_VBO = new VertexBuffer(m_Vertices.size() * sizeof(Vertex), &m_Vertices[0]);
		m_VBO->Generate();

		//glGenBuffers(1, &m_VBO);
		//glGenBuffers(1, &m_EBO);

		m_EBO = new ElementArrayBuffer(m_Indices.size() * sizeof(uint32_t), &m_Indices[0]);
		m_EBO->Generate();

		//glBindVertexArray(m_VAO);
		m_VAO->Bind();
		//glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		//glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);
		m_VBO->Bind();
		m_VBO->CopyToCurrent();

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);
		m_EBO->Bind();
		m_EBO->CopyToCurrent();

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, uvs));
		glEnableVertexAttribArray(1);

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

		ICE_INFO("Shutting down 2D renderer...");
	}
}
