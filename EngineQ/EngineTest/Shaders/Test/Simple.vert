#version 330 core
  
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoords;

layout (std140) uniform SomeUniforms
{
	mat4 view;
	mat4 projection;
};

out VS_OUT
{
	vec2 texCoords;
} vs_out;

void main()
{
	gl_Position = projection * view * vec4(position, 1.0f);

	vs_out.texCoords = texCoords;
}