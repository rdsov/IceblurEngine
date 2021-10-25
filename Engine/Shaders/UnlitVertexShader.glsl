#version 460 core
layout (location = 0) in vec3 POS;

uniform mat4 uModel;

void main()
{
    vec4 vertexPos = uModel * vec4(POS, 1.0);
    gl_Position = vertexPos;
}