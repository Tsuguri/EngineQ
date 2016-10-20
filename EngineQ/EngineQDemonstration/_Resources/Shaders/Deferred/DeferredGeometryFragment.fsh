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

void main()
{    

    gPosition = Position;

    gNormal = normalize(Normal);

    gAlbedoSpec.rgb = texture(diffuseTexture, TexCoords).rgb; //Color;//texture(diffuseTexture, TexCoords).rgb;

    gAlbedoSpec.a = 1;//texture(specularTexture, TexCoords).r;
}