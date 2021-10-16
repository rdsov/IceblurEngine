// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#pragma once

#include <glm/glm.hpp>

namespace Iceblur
{
    typedef uint32_t VID;

    struct Vertex
    {
        Vertex(float x, float y, float z, float s = 0, float t = 0)
                : position(glm::vec3(x, y, z)), uvs(glm::vec2(s, t))
        {
        }

        Vertex(const glm::vec3& pos, const glm::vec2& textureCoords)
                : position(pos), uvs(textureCoords)
        {
        }

        glm::vec3 position;
        glm::vec2 uvs;
    };

    struct Buffer
    {
        Buffer() : m_Id()
        {
        }

        virtual void Generate() = 0;

        virtual void Bind() = 0;

        virtual void CopyToCurrent() = 0;

        virtual void Delete() = 0;

        virtual VID GetId()
        {
            return m_Id;
        }

    protected:
        VID m_Id;
    };

    typedef signed long long int khronos_ssize_t;
    typedef khronos_ssize_t GLsizeiptr;

    struct VertexBuffer : Buffer
    {
        VertexBuffer(GLsizeiptr size, const void* data) : m_Size(size), m_Data(data)
        {
        }

        void Generate() override;

        void Bind() override;

        void CopyToCurrent() override;

        void AttribPointer();

        void Delete() override;

    private:
        GLsizeiptr m_Size;
        const void* m_Data;
    };
}
