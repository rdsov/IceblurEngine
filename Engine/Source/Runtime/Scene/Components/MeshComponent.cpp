// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "MeshComponent.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer/Renderer.h"
#include "Renderer/RenderingPipeline.h"
#include "Renderer/Shader.h"

#include "Scene/Entity.h"
#include "TransformComponent.h"

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

		m_VAO->AttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, uvs));
		m_VAO->EnableAttribArray(1);

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
			glm::mat4 transform = GetParentEntity()->Transform()->GetTransformMatrix();
			shader->SetUniformMatrix4fv("uModel", transform);
		}

		GetMeshData()->m_VAO->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}
