// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/Core.h"
#include "Core/CoreUtils.h"

namespace Iceblur
{
	struct TextureProps
	{
		TextureProps(IceString fileSource = "", bool useAlpha = false, bool flipTextureVertically = true, int wrapTextureS = 0, int wrapTextureT = 0,
		             int minTextureFilter = 0, int magTextureFilter = 0)
				: source(fileSource), flipVertically(flipTextureVertically), useAlphaChannel(useAlpha), wrapS(wrapTextureS), wrapT(wrapTextureT),
				  minFilter(minTextureFilter), magFilter(magTextureFilter)
		{
		}

		std::string source;
		bool flipVertically;
		bool useAlphaChannel;
		int wrapS, wrapT;
		int minFilter = 0x2601, magFilter = 0x2601;
	};

	class ICE_API Texture
	{
	public:
		Texture(const TextureProps& props = { })
				: m_Props(props)
		{
			Create(props);
		}

		~Texture()
		{
		}

		const uint32_t GetTexture() const
		{
			return m_Texture;
		}

		operator uint32_t() const
		{
			return m_Texture;
		}

		unsigned char* GetPixels() const
		{ return m_Pixels; }

		void Bind();

	protected:
		void Create(const TextureProps& props);

	private:
		TextureProps m_Props;
		uint32_t m_Texture;
		unsigned char* m_Pixels;
		int m_Width;
		int m_Height;
		int m_Channels;
	};
}
