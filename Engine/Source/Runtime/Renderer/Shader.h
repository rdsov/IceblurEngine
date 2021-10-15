// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

namespace Iceblur
{
    class Shader
    {
    public:
        Shader(const uint32_t& type, const std::string& path)
                : m_Shader()
        {
            Compile(type, path.c_str());
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

        void Attach(Shader* shader) const;

        void Link() const;

        void Use() const;

        operator uint32_t() const
        {
            return m_Program;
        }

    private:
        uint32_t m_Program;
    };
}
