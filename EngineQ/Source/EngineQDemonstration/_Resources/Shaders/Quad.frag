#version 330 core

layout(location = 0) out vec4 color;

in VS_DATA
{
	vec2 textureCoords;
} IN;

uniform sampler2D screenTexture;

void main()
{
    color = texture(screenTexture, IN.textureCoords);
}