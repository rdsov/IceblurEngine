#version 460 core
layout (location = 0) in vec3 POS;
layout (location = 1) in vec2 UVS;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec2 vTexCoords;

void main()
{
    vec4 vertexPos = uProjection * uView * uModel * vec4(POS, 1.0);
    vTexCoords = UVS;
    gl_Position = vertexPos;
}