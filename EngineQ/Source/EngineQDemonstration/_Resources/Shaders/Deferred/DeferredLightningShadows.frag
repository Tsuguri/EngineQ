#version 330 core

#include "../Common/Matrices.shh"
#include "../Common/Light.shh"

layout(location = 0) out vec4 FragColor;

in VS_DATA
{
	vec2 textureCoords;
} IN;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gColorSpecular;

uniform sampler2D testShadow;

uniform sampler2D ssaoTexture;

mat4 invView = inverse(matrices.view);
mat4 invProjection = inverse(matrices.projection);



float ShadowCalculations(Light light, sampler2D shadowMap, vec3 normal, vec3 position)
{
	if(!light.castsShadows)
		return 0.0f;
	
	vec4 fragPosLightSpace = light.lightMatrix * vec4(position, 1.0);

	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)

	float currentDepth = projCoords.z;

	const float samples = 4.0f;
	float bias = max(0.05f * (1.0f - dot(normal, -light.direction)), 0.005f);  
	vec2 offset = 10.0f / textureSize(shadowMap, 0);//(1.0f + (length(position)/30.0f))/ 25.0f;
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

	return (projCoords.z <= 1.0f ? 1.0f : 0.0f) * shadow;
}

float IsPointInShadow(Light light, sampler2D shadowMap, vec3 position)
{
	if(!light.castsShadows)
		return 0.0f;

	vec4 fragPosLightSpace = light.lightMatrix * vec4(position, 1.0);

	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)

	float currentDepth = projCoords.z;
	const float bias = 0.0005f;

    float projDepth = texture(shadowMap, projCoords.xy).r; 
	float shadow = (currentDepth - bias > projDepth) ? 1.0f : 0.0f;
	
	return ((projCoords.z <= 1.0f) ? 1.0f : 0.0f) * shadow;
}

float SamplePoint(Light light, sampler2D shadowMap, vec3 viewSpacePosition)
{
	const float samples = 128.0f;

	const float minDistance = 0.0f;
	float maxDistance = viewSpacePosition.z;

	float step = (maxDistance - minDistance) / samples;

	float shadow = 0.0f;
	for(float currentZ = minDistance; currentZ < maxDistance; currentZ += step)
	{
		vec4 rayPoint = invProjection * vec4(2.0f * IN.textureCoords - 1.0f, 1.0f, 1.0f);
		rayPoint.xyz /= rayPoint.w;
		
		vec3 direction = normalize(rayPoint.xyz);
		direction *= currentZ; 
		
		vec3 newWorldSpacePosition = (invView * vec4(direction, 1.0f)).xyz;

		shadow += IsPointInShadow(light, shadowMap, newWorldSpacePosition);
	}

	return shadow / samples;
}





void main()
{
	// Extract information from G-Buffer
	vec3 worldSpacePosition =  texture(gPosition, IN.textureCoords).xyz;//(invView * vec4(viewSpacePosition, 1.0f)).xyz;
	vec3 viewSpacePosition = (matrices.view * vec4(worldSpacePosition, 1.0f)).xyz;

	vec3 color = texture(gColorSpecular, IN.textureCoords).rgb;
	float materialSpecular = texture(gColorSpecular, IN.textureCoords).a;
	
	vec3 normal = normalize(texture(gNormal, IN.textureCoords).rgb);
	
	float ambientOcclusion = texture(ssaoTexture, IN.textureCoords).r;

	// TODO
	const vec3 materialAmbient = vec3(1.0f);
	const float materialShininess = 32;


	vec3 result = vec3(0.0f);

	// Directional lights
	for(int i = 0; i < lightCount; ++i)
	{
		Light light = lights[i];

	//	vec3 lightPosition = (matrices.view * vec4(light.position, 1.0f)).xyz;
		vec3 lightDir;
		float strength = 1.0f;

		if( light.type==0)
			lightDir = normalize(-light.direction);
		else
		{
			lightDir = normalize (worldSpacePosition - light.position);
			strength = 3.0f / length(worldSpacePosition - light.position);
		}
		// Ambient
		vec3 ambient = light.ambient * materialAmbient;

		// Diffuse
		float lightMultiplier = max(dot(normal, lightDir), 0.0f);
		vec3 diffuse = lightMultiplier * light.diffuse; /* TMP */ //* 10.0f;

		// Specular
		vec3 viewDir = normalize(-viewSpacePosition);
		vec3 halfwayDir = normalize(lightDir + viewDir);
		float spec = pow(max(dot(normal, halfwayDir), 0.0), materialShininess);
		vec3 specular = light.specular * spec * materialSpecular;

		// Shadows
		float shadow = 1.0f;
		if (light.type == 0)
		{
				if(i == 0) shadow = ShadowCalculations(light, lights_q_0_q_DirectionalShadowMap, normal, worldSpacePosition);
			else if(i == 1) shadow = ShadowCalculations(light, lights_q_1_q_DirectionalShadowMap, normal, worldSpacePosition);
			else if(i == 2) shadow = ShadowCalculations(light, lights_q_2_q_DirectionalShadowMap, normal, worldSpacePosition);
			else if(i == 3) shadow = ShadowCalculations(light, lights_q_3_q_DirectionalShadowMap, normal, worldSpacePosition);
			
			shadow = 1.0f - shadow;
		}
		else if (light.type == 1)
		{
			shadow = 0.0f;
			vec3 fragToLight = worldSpacePosition - light.position;

			float currentDepth = length(fragToLight);
			float depth = texture(lights_q_0_q_PointShadowMap, fragToLight).r;
			float bias = 0.00001;
			shadow = 1.0f;// currentDepth > depth ? 0.0f : 1.0f;
		}

		// Rays
		float raysShadow = 1.0f;
		     if(i == 0) raysShadow = SamplePoint(light, lights_q_0_q_DirectionalShadowMap, viewSpacePosition);
		else if(i == 1) raysShadow = SamplePoint(light, lights_q_1_q_DirectionalShadowMap, viewSpacePosition);
		else if(i == 2) raysShadow = SamplePoint(light, lights_q_2_q_DirectionalShadowMap, viewSpacePosition);
		else if(i == 3) raysShadow = SamplePoint(light, lights_q_3_q_DirectionalShadowMap, viewSpacePosition);
		
		float raysMultiplier = 1.0f;//viewSpacePosition.z * viewSpacePosition.z;
		raysShadow = (1.0f - raysShadow * raysMultiplier);
	
		
		
		result += ambient * color;

	}


	vec3 fragToLight = worldSpacePosition - lights[0].position;

	float currentDepth = length(fragToLight);
	float depth = texture(lights_q_0_q_PointShadowMap, fragToLight).r;

	FragColor = vec4(vec3(depth / 60.0f) + 0.1f * result, 1.0f);
}