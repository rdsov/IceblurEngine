// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"
#include "Scene/Component.h"
#include "Renderer/Intern/OpenGLData.h"

#include <vector>
#include <glm/glm.hpp>

namespace Iceblur
{
	class Texture;

	struct ICE_API MeshData
	{
		MeshData()
		{
		}

		MeshData(const std::vector<Vertex>& vertices, const std::vector<VID>& indices, const std::vector<Texture*>& textures)
				: m_Vertices(vertices), m_Indices(indices), m_Textures(textures)
		{
			Generate();
		}

		~MeshData()
		{
			Delete();
		}

		const std::vector<Vertex>& GetVertices() const
		{
			return m_Vertices;
		}

		//This needs to be done only once.
		//Binds the corresponding buffer objects and prepares the model for rendering.
		//Call this function only if you haven't initialized the constructor with mesh data.
		void Generate();

	private:
		void Delete();

		std::vector<Vertex> m_Vertices;
		std::vector<VID> m_Indices;
		std::vector<Texture*> m_Textures;

		VertexArrayObject* m_VAO = nullptr;
		VertexBuffer* m_VBO = nullptr;
		ElementArrayBuffer* m_EBO = nullptr;

		bool m_HasGenerated = false;

		friend class MeshComponent;
	};

	class ICE_API MeshComponent : public Component
	{
	public:
		ICE_COMPONENT_DECL(MeshComponent, false);

		MeshComponent(MeshData* meshData = nullptr) : m_Data(meshData)
		{
		}

		~MeshComponent()
		{
		}

		const MeshData* GetMeshData() const
		{
			return m_Data;
		}

		bool m_DrawIndexed = true;

		void Draw(const struct ShaderProgram* shader);

	private:
		void SetUniforms(const ShaderProgram* shader);

	private:
		MeshData* m_Data = nullptr;
	};
}
