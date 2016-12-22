#version 330 core

#include "../Common/Light.shh"

layout(location = 0) out vec4 color;

in VS_DATA
{
	vec2 textureCoords;
} IN;

uniform sampler2D worldPosition;
uniform sampler2D normal;
uniform sampler2D albedo;

uniform vec3 cameraPosition = vec3(1, 1, 1);

const float ambientStrength = 0.2f;
const float materialShininess = 32;

float ShadowCalculations(Light light, sampler2D shadowMap, vec3 position)
{
	if(!light.castsShadows)
		return 0.0f;
	
	vec4 fragPosLightSpace = light.lightMatrix * vec4(position, 1.0);

	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)

    float currentDepth = projCoords.z;

	const float samples = 6.0f;
	float bias = 0.0001;
//	float bias = max(0.05f * (1.0f - dot(normal, lightDir)), 0.005f);  
	vec2 offset = 10.0f / textureSize(shadowMap, 0);//(1.0f + (length(cameraPosition-position)/30.0f))/ 25.0f;
	vec2 pcfStep = 2.0f * offset / samples;

    float shadow = 0.0f;
	for(float x = -offset.x; x < offset.x; x += pcfStep.x)
	{
		for(float y = -offset.y; y < offset.y; y += pcfStep.y)
		{
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y)).r; 
			shadow += (currentDepth - bias > pcfDepth) ? 1.0f : 0.0f;
		}    
	}
	shadow *= 1.0f / (samples * samples);

	if(projCoords.z > 1.0f)
		shadow = 0.0f;

	return shadow;
}

void main()
{
	vec3 worldPos = texture(worldPosition,IN.textureCoords).xyz;
    vec3 colorTmp = texture(albedo, IN.textureCoords).rgb;
	float specularStrength = texture(albedo, IN.textureCoords).a;

	vec3 result = vec3(0.0f, 0.0f, 0.0f);

	for(int i = 0; i < lightCount; i++)
	{
		//ambient
		vec3 ambient = ambientStrength * lights[i].ambient;

		//diffuse
		vec3 norm = normalize(texture(normal,IN.textureCoords).rgb);
		vec3 dir = normalize(lights[i].position);
		float diff = max(dot(norm, dir), 0.0);
		vec3 diffuse = diff * lights[i].diffuse;

		//specular
		vec3 viewDir = normalize(cameraPosition - worldPos);
		vec3 halfwayDir = normalize(dir + viewDir);
		float spec = pow(max(dot(norm, halfwayDir), 0.0), materialShininess);
		vec3 specular = lights[0].specular * spec * specularStrength;

	//	float shadow = 1.0 - ShadowCalculations(lights[i], GetDirectionalLightSampler(i), worldPos);
		float shadow = 0.0f;
		     if(i == 0) shadow = 1.0 - ShadowCalculations(lights[i], lights_q_0_q_DirectionalShadowMap, worldPos);
		else if(i == 1) shadow = 1.0 - ShadowCalculations(lights[i], lights_q_1_q_DirectionalShadowMap, worldPos);
		else if(i == 2) shadow = 1.0 - ShadowCalculations(lights[i], lights_q_2_q_DirectionalShadowMap, worldPos);
		else if(i == 3) shadow = 1.0 - ShadowCalculations(lights[i], lights_q_3_q_DirectionalShadowMap, worldPos);

		vec3 res = (ambient + shadow * (diffuse + specular)) * colorTmp;
		result+=res;
	}
	
	color = vec4(result, 1.0f);

}