#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;

out VS_DATA
{
	vec2 textureCoords;
} OUT;

void main()
{
    gl_Position = vec4(position, 1.0f);
	OUT.textureCoords = texCoords;
}