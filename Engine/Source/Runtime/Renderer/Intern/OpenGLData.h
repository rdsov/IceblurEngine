// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Math/VMath.h"

#include "Core/CoreUtils.h"

namespace Iceblur
{
	struct Vertex
	{
		Vertex(float x, float y, float z, float nX, float nY, float nZ, float s = 0, float t = 0)
				: position(Vec3(x, y, z)), normal(nX, nY, nZ), uvs(Vec2(s, t))
		{
		}

		Vertex(const Vec3& pos, const Vec3& normalDirection, const Vec2& textureCoords)
				: position(pos), normal(normalDirection), uvs(textureCoords)
		{
		}

		Vec3 position;
		Vec3 normal;
		Vec2 uvs;
	};

	struct Buffer
	{
		Buffer() : m_Id()
		{
		}

		~Buffer()
		{
			Delete();
		}

		virtual void Generate();

		virtual void Bind() = 0;

		virtual void CopyToCurrent()
		{
		}

		virtual VID GetId()
		{
			return m_Id;
		}

	protected:
		void Delete();

		VID m_Id;
	};

	typedef signed long long int khronos_ssize_t;
	typedef khronos_ssize_t GLsizeiptr;

	struct VertexBuffer : Buffer
	{
		VertexBuffer(GLsizeiptr size, const void* data) : m_Size(size), m_Data(data)
		{
		}

		void Bind() override;

		void Unbind();

		void CopyToCurrent() override;

	private:
		GLsizeiptr m_Size;
		const void* m_Data;
	};

	struct ElementArrayBuffer : Buffer
	{
		ElementArrayBuffer(GLsizeiptr size, const void* data) : m_Size(size), m_Data(data)
		{
		}

		void Bind() override;

		void CopyToCurrent() override;

	private:
		GLsizeiptr m_Size;
		const void* m_Data;
	};

	struct VertexArrayObject : Buffer
	{
		VertexArrayObject() = default;

		void Generate() override;

		void Bind() override;

		void Unbind();

		void EnableAttribArray(VID id);

		void AttribPointer(VID position, int size, VID type, bool normalized, int stride, const void* data);
	};
}
