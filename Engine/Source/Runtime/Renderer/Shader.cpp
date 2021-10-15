// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Shader.h"

#include <glad/glad.h>

#include "Core/IO/Log.h"

namespace Iceblur
{
    void Shader::Compile(const uint32_t& type, const char* path)
    {
        std::ifstream file(path);

        if (!std::filesystem::exists(path))
        {
            ICE_ERROR(Error::EFailed::A_COMPILE_SHADER, { ICE_TOS(type), path });
            return;
        }

        std::string shaderStr((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        const char* shaderSource = shaderStr.c_str();

        m_Shader = glCreateShader(type);
        glShaderSource(m_Shader, 1, &shaderSource, nullptr);
        glCompileShader(m_Shader);

        int success;
        char infoLog[1024];
        glGetShaderiv(m_Shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(m_Shader, 1024, nullptr, infoLog);
            ICE_ERROR(Error::EFailed::A_COMPILE_SHADER, { ICE_TOS(type), path });
            ICE_ERROR(infoLog);
            return;
        }
    }

    void Shader::Delete() const
    {
        glad_glDeleteShader(m_Shader);
    }

    ShaderProgram::ShaderProgram()
    {
        m_Program = glCreateProgram();
    }

    void ShaderProgram::Attach(Shader* shader) const
    {
        glAttachShader(m_Program, *shader);
    }

    void ShaderProgram::Link() const
    {
        glLinkProgram(m_Program);

        int success;
        char infoLog[1024];

        glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_Program, 1024, nullptr, infoLog);
            ICE_ERROR(Error::EFailed::LINK_SHADER);
            ICE_ERROR(infoLog);
            return;
        }
    }

    void ShaderProgram::Use() const
    {
        glUseProgram(*this);
    }
}
