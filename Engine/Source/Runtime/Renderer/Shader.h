// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include "Core/CoreUtils.h"

#include <glm/glm.hpp>

namespace Iceblur
{
	class Shader
	{
	public:
		Shader(const uint32_t& type, IceString path)
				: m_Shader()
		{
			Compile(type, path.c_str());
		}

		~Shader()
		{
			Delete();
		}

		operator uint32_t() const
		{
			return m_Shader;
		}

		void Delete() const;

	private:
		void Compile(const uint32_t& type, const char* path);

		uint32_t m_Shader;
	};

	struct ShaderProgram
	{
		ShaderProgram();

		~ShaderProgram()
		{
			Delete();
		}

		void Attach(Shader* shader) const;

		void Link() const;

		void Use() const;

		void Delete() const;

		void SetUniformMatrix4fv(const char* name, const glm::mat4& value) const;

		operator uint32_t() const
		{
			return m_Program;
		}

	private:
		uint32_t m_Program;
	};
}
