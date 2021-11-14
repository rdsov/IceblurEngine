// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Texture.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION

#include "stb/stb_image.h"

#include "Core/IO/Log.h"
#include "Core/IO/VIO.h"

namespace Iceblur
{
	void Texture::Create(const TextureProps& props)
	{
		m_Props = props;

		if (props.source.empty())
		{
			return;
		}

		if (!VIO::Exists(props.source.c_str()))
		{
			ICE_ERROR(Error::ETypes::A_NOT_FOUND, { props.source });
			return;
		}

		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);

		stbi_set_flip_vertically_on_load(props.flipVertically);
		m_Pixels = stbi_load(props.source.c_str(), &m_Width, &m_Height, &m_Channels, 0);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, props.wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, props.wrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, props.minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, props.magFilter);

		if (m_Pixels)
		{
			int internalFormat, sourceFormat;
			if (m_Channels >= 4)
			{
				internalFormat = sourceFormat = GL_RGBA;
			}
			else if (m_Channels == 3)
			{
				internalFormat = sourceFormat = GL_RGB;
			}
			else
			{
				ICE_ERROR("File format of " + (std::string) props.source + " is not supported!");
				return;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, sourceFormat, GL_UNSIGNED_BYTE, m_Pixels);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			ICE_ERROR("Failed to load image from: " + props.source);
			return;
		}

		//m_HasTexture = true;
		stbi_image_free(m_Pixels);
	}

	void Texture::Bind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_Texture);
	}
}
