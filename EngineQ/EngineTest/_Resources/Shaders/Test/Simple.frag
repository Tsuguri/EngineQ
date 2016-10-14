#version 330 core

layout (location = 0) out vec4 color;

in VS_OUT
{
	vec2 texCoords;
} fs_in;

uniform sampler2D texture_diffuse;

void main()
{
	color = texture(texture_diffuse, fs_in.texCoords).rgba;
}