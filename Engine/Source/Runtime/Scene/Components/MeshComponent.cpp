// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "MeshComponent.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer/Renderer.h"
#include "Renderer/RenderingPipeline.h"
#include "Renderer/Shader.h"
#include "Renderer/Intern/Texture.h"

#include "Scene/Entity.h"
#include "TransformComponent.h"
#include "CameraComponent.h"

namespace Iceblur
{
	void MeshData::Generate()
	{
		if (m_HasGenerated)
		{
			return;
		}

		m_VAO = new VertexArrayObject();
		m_VAO->Generate();

		m_VBO = new VertexBuffer(m_Vertices.size() * sizeof(Vertex), &m_Vertices[0]);
		m_VBO->Generate();

		m_EBO = new ElementArrayBuffer(m_Indices.size() * sizeof(VID), &m_Indices[0]);
		m_EBO->Generate();

		m_VAO->Bind();
		m_VBO->Bind();
		m_VBO->CopyToCurrent();

		m_EBO->Bind();
		m_EBO->CopyToCurrent();

		m_VAO->AttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*) nullptr);
		m_VAO->EnableAttribArray(0);

		m_VAO->AttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, normal));
		m_VAO->EnableAttribArray(1);

		m_VAO->AttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, uvs));
		m_VAO->EnableAttribArray(2);

		m_VBO->Unbind();
		m_VAO->Unbind();

		m_HasGenerated = true;
	}

	void MeshData::Delete()
	{
		if (m_VBO)
		{
			delete m_VBO;
		}

		if (m_EBO)
		{
			delete m_EBO;
		}
	}

	void MeshComponent::Draw(const ShaderProgram* shader)
	{
		if (!GetMeshData())
		{
			return;
		}

		if (shader)
		{
			SetUniforms(shader);
		}

		for (const auto& texture : m_Data->m_Textures)
		{
			texture->Bind();
		}

		GetMeshData()->m_VAO->Bind();

		if (m_DrawIndexed)
		{
			glDrawElements(GL_TRIANGLES, GetMeshData()->m_Indices.size(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, GetMeshData()->m_Vertices.size());
		}
	}

	void MeshComponent::SetUniforms(const ShaderProgram* shader)
	{
		const std::string pipelineName = Renderer::GetCurrentPipeline()->GetName();

		if (pipelineName == "2D Renderer")
		{
			glm::mat4 transform = GetParentEntity()->Transform()->GetTransformMatrix();
			shader->SetUniformMatrix4fv("uModel", transform);
			shader->SetUniform3fv("uColor", Vec4(1.0f));
		}
		else if (pipelineName == "Realistic Renderer")
		{
			glm::mat4 transform = GetParentEntity()->Transform()->GetTransformMatrix();
			shader->SetUniformMatrix4fv("uModel", transform);

			shader->SetUniform3fv("uAmbientColor", Renderer::GetCurrentCamera()->GetPosition());

			Color ambient = Color(24, 32, 48);
			shader->SetUniform3fv("uAmbientColor", Vec3(RGB_CHANNELS(ambient.Normalized())));

			Color sun = Color(255, 239, 176);
			shader->SetUniform3fv("uSunColor", Vec3(RGB_CHANNELS(sun.Normalized())));
		}
	}
}
