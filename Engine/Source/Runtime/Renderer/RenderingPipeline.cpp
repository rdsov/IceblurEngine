// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "RenderingPipeline.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Intern/OpenGLData.h"
#include "Shader.h"

#include "Core/IO/Log.h"
#include "Core/IO/VIO.h"
#include "Core/WindowManager.h"

#include "Scene/SceneManager.h"
#include "Scene/Components/SpectatorCameraComponent.h"


namespace Iceblur
{
	void BaseRenderer::Refresh()
	{
		Resolution resolution = WindowManager::GetHost()->GetSize();
		glViewport(0, 0, resolution.GetWidth(), resolution.GetHeight());
	}

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
	}

	void BaseRenderer::Update(double deltaTime)
	{
		ClearColor();

		if (!m_Spectator)
		{
			ICE_ERROR("No spectator camera was found! Please add at least one camera to the current scene or setup a spectator camera.");
			return;
		}

		m_ShaderProgram->SetUniformMatrix4fv("uView", m_Spectator->GetViewMatrix());
		m_ShaderProgram->SetUniformMatrix4fv("uProjection", m_Spectator->GetProjectionMatrix());
		m_Spectator->Update(deltaTime);

		SceneManager::Update(deltaTime);
	}

	void BaseRenderer::ClearColor()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(ALL_COLOR_CHANNELS(m_ClearColor));
	}

	void BaseRenderer::Shutdown()
	{
		delete m_ShaderProgram;

		ICE_PRINT("Shutting down 2D renderer...");
	}
}
