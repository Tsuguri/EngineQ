#version 330 core

layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec4 gAlbedoSpec;

in VS_DATA
{
	vec3 position;
	vec2 textureCoords;
	vec3 color;
	vec3 normal;
} IN;

#include "../Common/Material.shh"

uniform Material material;

void main()
{    
    gPosition = IN.position;

    gNormal = normalize(IN.normal);

    gAlbedoSpec.rgb = texture(material.diffuseTexture, IN.textureCoords).rgb * material.diffuse;

    gAlbedoSpec.a = 1;
}