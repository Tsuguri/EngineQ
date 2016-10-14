#version 330 core

layout(location = 0)in vec3 positionIn;
layout(location = 3)in vec3 normalIn;
layout(location = 2)in vec3 colorIn;

out vec3 Position;
out vec3 TexCoords;//here change to vec2 when apply texture
out vec3 Normal;

const mat4 IdMat = mat4(1.0);

uniform mat4 ModelMat = IdMat;
uniform mat4 ViewMat = IdMat;
uniform mat4 ProjMat = IdMat;

mat4 MVP = ProjMat*ViewMat*ModelMat;
mat3 NormalMat = mat3(transpose(inverse(ModelMat)));

void main()
{
    vec4 worldPos = ModelMat * vec4(positionIn, 1.0f);
    Position = worldPos.xyz; 
    gl_Position = ProjMat * ViewMat * worldPos;
    TexCoords = colorIn;

    Normal = NormalMat * normalIn;
}  