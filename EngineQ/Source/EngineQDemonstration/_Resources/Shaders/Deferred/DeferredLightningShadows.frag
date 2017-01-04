#version 330 core

#include "../Common/Matrices.shh"
#include "../Common/Light.shh"

layout(location = 0) out
vec4 FragColor;

in VS_DATA
{
vec2 textureCoords;
}
IN;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gColorSpecular;

uniform sampler2D ssaoTexture;

mat4 invView = inverse(matrices.view);
mat4 invProjection = inverse(matrices.projection);

uniform bool useSSAO;
uniform bool usePCF;
uniform bool useRays;

float DirectionalShadowCalculations(Light light, sampler2D shadowMap, vec3 normal, vec3 position)
{
	if (!light.castsShadows)
		return 0.0f;
	
	vec4 fragPosLightSpace = light.lightMatrix * vec4(position, 1.0);
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
	    
	float currentDepth = projCoords.z;
	float bias = max(0.05f * (1.0f - dot(normal, -light.direction)), 0.005f) * 0.1f;
		
	float shadow = 0.0f;
	if (usePCF)
	{
		const float samples = 8.0f;
		vec2 offset = 8.0f / textureSize(shadowMap, 0); //(1.0f + (length(position)/30.0f))/ 25.0f;
		vec2 pcfStep = 2.0f * offset / samples;

		for (float x = -offset.x; x < offset.x; x += pcfStep.x)
		{
			for (float y = -offset.y; y < offset.y; y += pcfStep.y)
			{
				float closestDepth = texture(shadowMap, projCoords.xy + vec2(x, y)).r;
				shadow += (currentDepth - bias > closestDepth) ? 1.0f : 0.0f;
			}
		}
		shadow *= 1.0f / (samples * samples);
	}
	else
	{
		float closestDepth = texture(shadowMap, projCoords.xy).r;
		shadow = (currentDepth - bias > closestDepth) ? 1.0f : 0.0f;
	}
	
	return (projCoords.z <= 1.0f ? 1.0f : 0.0f) * shadow;
}

float PointShadowCalculations(Light light, samplerCube shadowMap, vec3 normal, vec3 position)
{
	if (!light.castsShadows)
		return 0.0f;

	vec3 fragToLight = position - light.position;

	float currentDepth = length(fragToLight);
	float bias = max(0.05f * (1.0f - dot(normal, -light.direction)), 0.005f);

	float shadow = 0.0f;
	if (usePCF)
	{
		const float samples = 4.0f;
		float offset = (1.0f + (currentDepth / light.farPlane)) / 25.0f;
		float pcfStep = 2.0f * offset / samples;

		for (float x = -offset; x < offset; x += pcfStep)
		{
			for (float y = -offset; y < offset; y += pcfStep)
			{
				for (float z = -offset; z < offset; z += pcfStep)
				{
					float closestDepth = texture(shadowMap, fragToLight + vec3(x, y, z)).r;
					shadow += (currentDepth - bias > closestDepth) ? 1.0f : 0.0f;
				}
			}
		}
		shadow *= 1.0f / (samples * samples * samples);
	}
	else
	{
		float closestDepth = texture(shadowMap, fragToLight).r;
		shadow = (currentDepth - bias > closestDepth) ? 1.0f : 0.0f;
	}

	return shadow;
}

float IsPointInShadow(Light light, sampler2D shadowMap, vec3 position)
{
	if (!light.castsShadows)
		return 0.0f;

	vec4 fragPosLightSpace = light.lightMatrix * vec4(position, 1.0);
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
    
	float currentDepth = projCoords.z;
	const float bias = 0.0005f;

	float projDepth = texture(shadowMap, projCoords.xy).r;
	float shadow = (currentDepth - bias > projDepth) ? 1.0f : 0.0f;
	
	return ((projCoords.z <= 1.0f) ? 1.0f : 0.0f) * shadow;
}

float SamplePoint(Light light, sampler2D shadowMap, vec3 cameraPosition, float cameraFragmentDistance)
{
	const float samples = 32.0f;

	const float minDistance = 0.0f;
	float maxDistance = cameraFragmentDistance;

	float step = (maxDistance - minDistance) / samples;

	vec4 rayPoint = invProjection * vec4(2.0f * IN.textureCoords - 1.0f, 1.0f, 1.0f);
	rayPoint.xyz /= rayPoint.w;
	vec3 direction = normalize(mat3(invView) * rayPoint.xyz);
		
	float shadow = 0.0f;
	for (float currentZ = minDistance; currentZ < maxDistance; currentZ += step)
	{
		vec3 newWorldSpacePosition = cameraPosition + direction * currentZ;

		shadow += IsPointInShadow(light, shadowMap, newWorldSpacePosition);
	}

	return shadow / samples;
}


void main()
{
	// Extract information from G-Buffer
	vec3 color = texture(gColorSpecular, IN.textureCoords).rgb;
	float materialSpecular = texture(gColorSpecular, IN.textureCoords).a;

	// World space G-Buffer
	//	vec3 worldSpacePosition = texture(gPosition, IN.textureCoords).xyz;
	//	vec3 viewSpacePosition = (matrices.view * vec4(worldSpacePosition, 1.0f)).xyz;
	//	
	//	vec3 worldSpaceNormal = normalize(texture(gNormal, IN.textureCoords).xyz);
	//	vec3 viewSpaceNormal = normalize(mat3(transpose(invView)) * worldSpaceNormal);
	
	// View space G-Buffer
	vec3 viewSpacePosition = texture(gPosition, IN.textureCoords).xyz;
	vec3 worldSpacePosition = (invView * vec4(viewSpacePosition, 1.0f)).xyz;
	
	vec3 viewSpaceNormal = normalize(texture(gNormal, IN.textureCoords).xyz);
	vec3 worldSpaceNormal = normalize(mat3(transpose(matrices.view)) * viewSpaceNormal);

	float ambientOcclusion = 1.0f;
	if (useSSAO)
	{
		ambientOcclusion = texture(ssaoTexture, IN.textureCoords).r;
	}

	// Camera data
	vec3 cameraPosition = invView[3].xyz;
	vec3 viewDir = cameraPosition - worldSpacePosition;
	float viewDirLength = length(viewDir);
	viewDir /= viewDirLength;


	// TODO
	const vec3 materialAmbient = vec3(1.0f);
	const float materialShininess = 32;


	// Lighting
	// All calculations in world space
	vec3 result = vec3(0.0f);
	for (int i = 0; i < lightCount; ++i)
	{
		Light light = lights[i];

		vec3 lightDir;
		float strength = 1.0f;

		if (light.type == 0)
		{
			lightDir = normalize(-light.direction);
		}
		else
		{
			lightDir = light.position - worldSpacePosition;
			float lightDirLengthInv = 1.0f / length(lightDir);

			strength = 3.0f * lightDirLengthInv;
			lightDir *= lightDirLengthInv;
		}


		// Ambient
		vec3 ambient = light.ambient * materialAmbient;


		// Diffuse
		float lightMultiplier = max(dot(worldSpaceNormal, lightDir), 0.0f);
		vec3 diffuse = lightMultiplier * light.diffuse;


		// Specular
		vec3 halfwayDir = normalize(lightDir + viewDir);
		float spec = pow(max(dot(worldSpaceNormal, halfwayDir), 0.0), materialShininess);
		vec3 specular = light.specular * spec * materialSpecular;


		// Shadows
		float shadow = 0.0f;
		float raysShadow = 0.0f;
		
		// Directional lights
		if (light.type == 0)
		{
			if (i == 0)
				shadow = DirectionalShadowCalculations(light, lights_q_0_q_DirectionalShadowMap, worldSpaceNormal, worldSpacePosition);
			else if (i == 1)
				shadow = DirectionalShadowCalculations(light, lights_q_1_q_DirectionalShadowMap, worldSpaceNormal, worldSpacePosition);
			else if (i == 2)
				shadow = DirectionalShadowCalculations(light, lights_q_2_q_DirectionalShadowMap, worldSpaceNormal, worldSpacePosition);
			else if (i == 3)
				shadow = DirectionalShadowCalculations(light, lights_q_3_q_DirectionalShadowMap, worldSpaceNormal, worldSpacePosition);

			if (useRays)
			{
				if (i == 0)
					raysShadow = SamplePoint(light, lights_q_0_q_DirectionalShadowMap, cameraPosition, viewDirLength);
				else if (i == 1)
					raysShadow = SamplePoint(light, lights_q_1_q_DirectionalShadowMap, cameraPosition, viewDirLength);
				else if (i == 2)
					raysShadow = SamplePoint(light, lights_q_2_q_DirectionalShadowMap, cameraPosition, viewDirLength);
				else if (i == 3)
					raysShadow = SamplePoint(light, lights_q_3_q_DirectionalShadowMap, cameraPosition, viewDirLength);
			}
		}
		// Point lights
		else if (light.type == 1)
		{
			if (i == 0)
				shadow = PointShadowCalculations(light, lights_q_0_q_PointShadowMap, worldSpaceNormal, worldSpacePosition);
			else if (i == 1)
				shadow = PointShadowCalculations(light, lights_q_1_q_PointShadowMap, worldSpaceNormal, worldSpacePosition);
			else if (i == 2)
				shadow = PointShadowCalculations(light, lights_q_2_q_PointShadowMap, worldSpaceNormal, worldSpacePosition);
			else if (i == 3)
				shadow = PointShadowCalculations(light, lights_q_3_q_PointShadowMap, worldSpaceNormal, worldSpacePosition);
		}

		shadow = 1.0f - shadow;
		float raysMultiplier = 1.0f; //viewSpacePosition.z * viewSpacePosition.z;
		raysShadow = (1.0f - raysShadow * raysMultiplier);
		
		result += (ambient + shadow * (diffuse + specular)) * color * raysShadow * ambientOcclusion;
	}

	FragColor = vec4(result, 1.0f);
}