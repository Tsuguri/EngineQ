#version 330 core

layout (location = 0) in vec3 position;

#include "../Common/Matrices.shh"

out vec3 pos;
void main()
{
    vec4 modelPos = matrices.model * vec4(position, 1.0f);
    pos = modelPos.xyz;
    gl_Position = matrices.view * modelPos;
    gl_Position.x = -gl_Position.x;
}