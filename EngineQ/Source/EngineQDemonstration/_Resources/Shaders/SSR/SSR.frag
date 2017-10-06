#version 330 core

layout(location = 0) out vec4 FragColor;

in VS_DATA
{
	vec2 textureCoords;
} IN;

#include "../Common/Matrices.shh"

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gColorSpecular;
uniform sampler2D scene;

uniform bool enabled;

// Consts should help improve performance
const float rayStep = 0.05f;
const float minRayStep = 0.01f;
const float maxSteps = 128.0f;
const float searchDist = 4.0f;
const float searchDistInv = 1.0f / searchDist;
const int numBinarySearchSteps = 32;
//const float maxDDepth = 1.0;
//const float maxDDepthInv = 1.0;

const float minDDepth = 0.05f;

const float reflectionSpecularFalloffExponent = 3.0;


vec3 BinarySearch(vec3 dir, inout vec3 hitCoord, out float dDepth)
{
	float depth;

	for (int i = 0; i < numBinarySearchSteps; i++)
	{
		vec4 projectedCoord = matrices.projection * vec4(hitCoord, 1.0f);
		projectedCoord.xy /= projectedCoord.w;
		projectedCoord.xy = projectedCoord.xy * 0.5f + 0.5f;

		depth = texture(gPosition, projectedCoord.xy).z;
		dDepth = hitCoord.z - depth;

		dir *= 0.5f;
		if (dDepth < 0.0f)
			hitCoord += dir;
		else
			hitCoord -= dir;
	}

	vec4 projectedCoord = matrices.projection * vec4(hitCoord, 1.0f);
	projectedCoord.xy /= projectedCoord.w;
	projectedCoord.xy = projectedCoord.xy * 0.5f + 0.5f;

	return vec3(projectedCoord.xy, depth);
}
 
 
vec4 RayCast(vec3 dir, inout vec3 hitCoord, out float dDepth)
{
	dir *= rayStep;
 
	float depth;
	for (int i = 0; i < maxSteps; ++i)
	{
		hitCoord += dir;
 
		vec4 projectedCoord = matrices.projection * vec4(hitCoord, 1.0f);
		projectedCoord.xy /= projectedCoord.w;
		projectedCoord.xy = projectedCoord.xy * 0.5f + 0.5f;
 
		depth = texture(gPosition, projectedCoord.xy).z;
		dDepth = hitCoord.z - depth;
 
		if (dDepth > minDDepth)
		{
			vec4 result = vec4(BinarySearch(dir, hitCoord, dDepth), 1.0f);
			if (abs(dDepth) > minDDepth)
				return vec4(0.0f);
			
			return result;
		}
	}
 
	return vec4(0.0f);
}
 
 
void main()
{
	// Samples
	float specular = texture(gColorSpecular, IN.textureCoords).a;
	vec3 sceneColor = texture(scene, IN.textureCoords).rgb;

	if (!enabled || specular == 0.0f)
	{
		FragColor = vec4(sceneColor, 1.0f);
		return;
	}
	specular = clamp(specular, 0.0f, 1.0f);

	vec3 viewNormal = texture(gNormal, IN.textureCoords).xyz;
	vec3 viewPos = texture(gPosition, IN.textureCoords).xyz;

	// Reflection vector
	vec3 reflected = normalize(reflect(normalize(viewPos), normalize(viewNormal)));

	// Ray cast
	vec3 hitPos = viewPos;
	float dDepth;

	vec4 coords = RayCast(reflected * max(minRayStep, viewPos.z), hitPos, dDepth);

	vec2 dCoords = abs(vec2(0.5f) - coords.xy);
	float screenEdgefactor = clamp(1.0f - (dCoords.x + dCoords.y), 0.0f, 1.0f);

	vec3 reflectionColor = texture(scene, coords.xy).rgb;
	float reflectionMultiplier = 
	//	pow(specular, reflectionSpecularFalloffExponent) *
		specular * 
		screenEdgefactor * clamp(reflected.z, 0.0f, 1.0f) *
		clamp((searchDist - length(viewPos - hitPos)) * searchDistInv, 0.0f, 1.0f) * coords.w;

	// Get color
	FragColor = vec4(sceneColor * (1.0f - reflectionMultiplier) + reflectionColor * reflectionMultiplier, 1.0f);
//	FragColor -= vec4(reflectionColor, 1.0f);
//	FragColor += vec4(vec3(reflectionMultiplier), 1.0f);
}