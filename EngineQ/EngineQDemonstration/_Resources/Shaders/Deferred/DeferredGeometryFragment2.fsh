#version 330 core

out vec3 gPosition;
out vec3 gNormal;
out vec4 gAlbedoSpec;

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

    gAlbedoSpec.rgb = vec3(1, 0, 0); //Color;//texture(diffuseTexture, TexCoords).rgb;

    gAlbedoSpec.a = 1;//texture(specularTexture, TexCoords).r;
}