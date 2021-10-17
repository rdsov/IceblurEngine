// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "OpenGLData.h"

#include <glad/glad.h>

namespace Iceblur
{
	void Buffer::Generate()
	{
		glGenBuffers(1, &m_Id);
	}

	void Buffer::Delete()
	{
		glDeleteBuffers(1, &m_Id);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::CopyToCurrent()
	{
		glBufferData(GL_ARRAY_BUFFER, m_Size, m_Data, GL_STATIC_DRAW);
	}

	void ElementArrayBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
	}

	void ElementArrayBuffer::CopyToCurrent()
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Size, m_Data, GL_STATIC_DRAW);
	}

	void VertexArrayObject::Generate()
	{
		glGenVertexArrays(1, &m_Id);
	}

	void VertexArrayObject::Bind()
	{
		glBindVertexArray(m_Id);
	}

	void VertexArrayObject::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArrayObject::EnableAttribArray(VID id)
	{
		glEnableVertexAttribArray(id);
	}

	void VertexArrayObject::AttribPointer(VID position, int size, VID type, bool normalized, int stride, const void* data)
	{
		glVertexAttribPointer(position, size, type, normalized, stride, data);
	}
}
