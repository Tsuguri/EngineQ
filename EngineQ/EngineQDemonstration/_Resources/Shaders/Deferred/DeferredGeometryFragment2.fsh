#version 330 core

layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec4 gAlbedoSpec;

in vec3 Position;
in vec2 TexCoords;
in vec3 Color;
in vec3 Normal;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform vec3 myColor;

void main()
{    

    gPosition = Position;

    gNormal = normalize(Normal);

    gAlbedoSpec.rgb = myColor;

    gAlbedoSpec.a = 1;
}