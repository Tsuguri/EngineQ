#version 330 core

#include "../Common/Light.shh"


in vec2 TexCoords;

uniform sampler2D worldPosition;
uniform sampler2D normal;
uniform sampler2D albedo;

out vec4 color;

uniform vec3 cameraPosition = vec3(1, 1, 1);

const float ambientStrength=0.2f;
const float specularStrength=0.3f;
const float materialShininess=32;

float ShadowCalculations(Light light, sampler2D shadowMap, vec3 position)
{
	if(!light.castsShadows)
		return 0.0f;
	
	vec4 fragPosLightSpace = light.lightMatrix * vec4(position, 1.0);

	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // Check whether current frag pos is in shadow
    float shadow = currentDepth >= closestDepth  ? 1.0 : 0.0;

	if(projCoords.z > 1.0)
        shadow = 0.0;

	return shadow;
}

void main()
{
	vec3 worldPos = texture(worldPosition,TexCoords).xyz;

    vec3 colorTmp = texture(albedo, TexCoords).rgb;

	//ambient
	vec3 ambient = ambientStrength*lights[0].ambient;

	//diffuse
	vec3 norm = normalize(texture(normal,TexCoords).rgb);
	vec3 dir = normalize(lights[0].position);
	float diff = max(dot(norm, dir), 0.0);
	vec3 diffuse = diff * lights[0].diffuse;
	float shadow = 1.0 - ShadowCalculations(lights[0], lights_q_0_q_shadowMap, worldPos);


	//specular
	vec3 viewDir = normalize(cameraPosition - worldPos);
	vec3 halfwayDir = normalize(dir + viewDir);
	float spec = pow(max(dot(norm, halfwayDir), 0.0), materialShininess);
	vec3 specular = lights[0].specular * spec*specularStrength;

	vec3 result = (ambient + shadow*(diffuse + specular) ) * colorTmp;
	color = vec4(result,1.0);
	//color = vec4(vec3(shadow),1.0);
	//color = vec4(vec3(texture(lights_q_0_q_shadowMap, TexCoords).r),1.0);
}