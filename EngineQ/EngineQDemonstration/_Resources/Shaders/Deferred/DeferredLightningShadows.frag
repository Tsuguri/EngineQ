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

    float currentDepth = projCoords.z;

    float shadow = 0.0;

	float samples = 4.0;
	float bias = 0.0001;
	vec2 offset = 1.0/ textureSize(shadowMap, 0);//(1.0 + (length(cameraPosition-position)/30.0))/ 25.0;
	vec2 pcfStep = 2.0 * offset / samples;

	for(float x = -offset.x; x < offset.x; x+=pcfStep.x)
	{
		for(float y = -offset.y; y < offset.y; y+=pcfStep.y)
		{
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y)).r; 

			if(currentDepth - bias > pcfDepth)
				shadow+=1.0;
		}    
	}
	shadow /= samples*samples;

	if(projCoords.z > 1.0)
        shadow = 0.0;

	return shadow;
}

void main()
{
	vec3 worldPos = texture(worldPosition,IN.textureCoords).xyz;
    vec3 colorTmp = texture(albedo, IN.textureCoords).rgb;
	vec3 result = vec3(0.0,0.0,0.0);


	for(int i = 0; i < lightCount; i++)
	{
		//ambient
		vec3 ambient = ambientStrength*lights[i].ambient;

		//diffuse
		vec3 norm = normalize(texture(normal,IN.textureCoords).rgb);
		vec3 dir = normalize(lights[i].position);
		float diff = max(dot(norm, dir), 0.0);
		vec3 diffuse = diff * lights[i].diffuse;

		//specular
		vec3 viewDir = normalize(cameraPosition - worldPos);
		vec3 halfwayDir = normalize(dir + viewDir);
		float spec = pow(max(dot(norm, halfwayDir), 0.0), materialShininess);
		vec3 specular = lights[0].specular * spec*specularStrength;

		float shadow = 1.0 - ShadowCalculations(lights[i], GetLightSampler(i), worldPos);
		vec3 res = (ambient + shadow * (diffuse + specular)) * colorTmp;
		result+=res;
	}

	color = vec4(result,1.0);

}