#version 330 core

layout (location = 0) in vec3 position;

#include "../Common/Matrices.shh"

void main()
{
    gl_Position = matrices.projection * matrices.view * matrices.model * vec4(position, 1.0f);
}