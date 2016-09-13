#version 330 core

in vec2 TexCoords;

uniform sampler2D worldPosition;
uniform sampler2D normal;
uniform sampler2D albedo;

out vec4 color;


void main()
{
    if(true)
        color=texture(worldPosition, TexCoords);
    else if (false)
        color=texture(normal, TexCoords);
    else
        color =texture(screenTexture, TexCoords);
}