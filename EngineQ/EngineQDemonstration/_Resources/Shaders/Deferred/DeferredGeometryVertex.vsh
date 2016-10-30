#version 330 core

layout(location = 0) in vec3 positionIn;
layout(location = 1) in vec2 texCoordsIn;
layout(location = 2) in vec3 colorIn;
layout(location = 3) in vec3 normalIn;

out VS_DATA
{
	vec3 position;
	vec2 textureCoords;
	vec3 color;
	vec3 normal;
} OUT;

#include "../Common/Matrices.shh"

uniform Matrices matrices;

//	mat4 MVP = matrices.projection * matrices.view * matrices.model;
mat3 NormalMat = mat3(transpose(inverse(matrices.model)));

void main()
{
    vec4 worldPos = matrices.model * vec4(positionIn, 1.0f);
    gl_Position = matrices.projection * matrices.view * worldPos;

    OUT.position = worldPos.xyz; 
	OUT.textureCoords = vec2(1.0f - texCoordsIn.x, texCoordsIn.y);
	OUT.color = colorIn;
    OUT.normal = NormalMat * normalIn;
}  