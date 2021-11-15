#version 460 core
layout (location = 0) in vec3 POS;
layout (location = 1) in vec3 NORMAL;
layout (location = 2) in vec2 UVS;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 vNormal;
out vec2 vTexCoords;
out vec3 vPixelPos;

void main()
{
    vec4 vertexPos = uProjection * uView * uModel * vec4(POS, 1.0);

    vNormal = mat3(transpose(inverse(uModel))) * NORMAL;
    vTexCoords = UVS;
    vPixelPos = vec3(uModel * vec4(POS, 1.0));

    gl_Position = vertexPos;
}