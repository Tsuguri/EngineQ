#version 330 core

#include "../Common/Light.shh"


in vec2 TexCoords;

uniform sampler2D worldPosition;
uniform sampler2D normal;
uniform sampler2D albedo;

out vec4 color;

uniform vec3 cameraPosition = vec3(1, 1, 1);

const float ambientStrength=0.5f;
const float specularStrength=0.3f;
const float materialShininess=32;

float ShadowCalculations(Light light, sampler2D shadowMap, vec3 worldPosition, vec3 position)
{
	if(!light.castsShadows)
		return 0.0f;
	
	vec4 fragPosLightSpace = light.lightMatrix * vec4(position, 1.0);
}

void main()
{
    vec3 colorTmp = texture(albedo, TexCoords).rgb;

	//ambient
	vec3 ambient = ambientStrength*lights[0].ambient;
	vec3 map = texture(lights_q_0_q_shadowMap,TexCoords).xyz;
	//diffuse
	vec3 norm = normalize(texture(normal,TexCoords).rgb);
	vec3 dir = normalize(lights[0].position);
	float diff = max(dot(norm, dir), 0.0);
	vec3 diffuse = diff * lights[0].diffuse;
		

	//specular
	vec3 viewDir = normalize(cameraPosition - texture(worldPosition,TexCoords).xyz);
	vec3 halfwayDir = normalize(dir + viewDir);
	float spec = pow(max(dot(norm, halfwayDir), 0.0), materialShininess);
	vec3 specular = lights[0].specular * spec*specularStrength;
	vec3 result = (ambient + diffuse + specular) * colorTmp;
	color = vec4(result,1.0);
}