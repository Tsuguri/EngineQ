#version 330 core

out vec3 gPosition;
out vec3 gNormal;
out vec4 gAlbedoSpec;

in vec3 Position;
in vec3 TexCoords;
in vec3 Normal;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

void main()
{    

    gPosition = Position;

    gNormal = normalize(Normal);

    gAlbedoSpec.rgb = TexCoords;//texture(diffuseTexture, TexCoords).rgb;

    gAlbedoSpec.a = texture(specularTexture, TexCoords.xy).r;
}