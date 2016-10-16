#version 330 core

layout(location = 0)in vec3 positionIn;
layout(location = 1)in vec2 texCoordsIn;
layout(location = 2)in vec3 colorIn;
layout(location = 3)in vec3 normalIn;

out vec3 Position;
out vec2 TexCoords;
out vec3 Color;
out vec3 Normal;

struct Matrices
{
	mat4 Model;
	mat4 View;
	mat4 Projection;
};

uniform Matrices matrices;

mat4 MVP = matrices.Projection * matrices.View * matrices.Model;
mat3 NormalMat = mat3(transpose(inverse(matrices.Model)));

void main()
{
    vec4 worldPos = matrices.Model * vec4(positionIn, 1.0f);
    Position = worldPos.xyz; 
    gl_Position = matrices.Projection * matrices.View * worldPos;
    TexCoords = vec2(texCoordsIn.x, 1.0f - texCoordsIn.y);
	Color = colorIn;

    Normal = NormalMat * normalIn;
}  