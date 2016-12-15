#version 330 core

#include "../Common/Light.shh"

const int MaxLights = 4;
in vec2 TexCoords;

uniform sampler2D worldPosition;
uniform sampler2D normal;
uniform sampler2D albedo;

out vec4 color;

uniform float time =0.0f;
uniform vec3 cameraPosition = vec3(1, 1, 1);
uniform vec3 lightDir = vec3(1, 1, 0);
uniform vec3 lightColor = vec3(1,1,1);
const float ambientStrength=0.3f;
const float specularStrength=0.1f;
const float materialShininess=32;

vec3 light = 3 * vec3(cos(time), 1, sin(time));

void main()
{
    vec3 colorTmp = texture(albedo, TexCoords).rgb;

	//ambient
	vec3 ambient = ambientStrength*lightColor;

	//diffuse
	vec3 norm = normalize(texture(normal,TexCoords).rgb);
	vec3 dir = normalize(light);
	float diff = max(dot(norm, dir), 0.0);
	vec3 diffuse = diff * lightColor;
		

	//specular
	vec3 viewDir = normalize(cameraPosition - texture(worldPosition,TexCoords).xyz);
	vec3 halfwayDir = normalize(dir + viewDir);
	float spec = pow(max(dot(norm, halfwayDir), 0.0), materialShininess);
	vec3 specular = lightColor * spec*specularStrength;
	vec3 result = (ambient + diffuse + specular) * colorTmp;
	color = vec4(result,1.0);
}