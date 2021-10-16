// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "RenderingPipeline.h"

#include <glad/glad.h>

#include "Core/IO/Log.h"
#include "Core/IO/VIO.h"
#include "Intern/OpenGLData.h"

namespace Iceblur
{
	uint32_t m_VAO;
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

		glGenVertexArrays(1, &m_VAO);

		VertexBuffer vertexBuffer(m_Vertices.size() * sizeof(Vertex), &m_Vertices[0]);
		vertexBuffer.Generate();

		//glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);
		//glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		vertexBuffer.Bind();
		//glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);
		vertexBuffer.CopyToCurrent();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, uvs));
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
		delete m_ShaderProgram;
		ICE_INFO("Shutting down 2D renderer...");
	}
}
