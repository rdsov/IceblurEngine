#version 460 core

out vec4 FragColor;

uniform vec4 uColor;
uniform sampler2D uTexture;

in vec2 vTexCoords;

void main()
{
    vec4 result = texture(uTexture, vTexCoords) * uColor;
    FragColor = result;
}