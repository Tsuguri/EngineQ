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

mat4 ModelView = matrices.view * matrices.model;
mat4 ViewProjection = matrices.projection * matrices.view;
mat3 NormalMat = mat3(transpose(inverse(ModelView)));

void main()
{
    vec4 viewPos = matrices.model * vec4(positionIn, 1.0f);
    gl_Position = ViewProjection * viewPos;

    OUT.position = viewPos.xyz; 
	OUT.textureCoords = vec2(1.0f - texCoordsIn.x, texCoordsIn.y);
	OUT.color = colorIn;
    OUT.normal = normalize(NormalMat * normalIn);
}  