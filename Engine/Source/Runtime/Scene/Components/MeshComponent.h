// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"
#include "Scene/Component.h"
#include "Renderer/Intern/OpenGLData.h"

#include <vector>
#include <glm/glm.hpp>

namespace Iceblur
{
	struct MeshData
	{
		MeshData()
		{
		}

		MeshData(const std::vector<Vertex>& vertices, const std::vector<VID>& indices)
				: m_Vertices(vertices), m_Indices(indices)
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

		VertexArrayObject* m_VAO = nullptr;
		VertexBuffer* m_VBO = nullptr;
		ElementArrayBuffer* m_EBO = nullptr;

		bool m_HasGenerated = false;

		friend class MeshComponent;
	};

	class MeshComponent : public Component
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

		void Draw(const struct ShaderProgram* shader);

	private:
		MeshData* m_Data = nullptr;
	};
}
