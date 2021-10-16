// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "OpenGLData.h"

#include <glad/glad.h>

namespace Iceblur
{
	void VertexBuffer::Generate()
	{
		glGenBuffers(1, &m_Id);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
	}

	void VertexBuffer::CopyToCurrent()
	{
		glBufferData(GL_ARRAY_BUFFER, m_Size, m_Data, GL_STATIC_DRAW);
	}

	void VertexBuffer::AttribPointer()
	{
		//glVertexAttribPointer()
	}

	void VertexBuffer::Delete()
	{
		glDeleteBuffers(1, &m_Id);
	}
}
