#version 330 core

layout(location = 0) out float FragColor;

in VS_DATA
{
	vec2 textureCoords;
} IN;

#include "../Common/Matrices.shh"

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D noiseTexture;

const int maxKernelSize = 128;
uniform int kernelSize = 64;

uniform vec3 samples[maxKernelSize];

uniform float radius = 1.0f;
uniform float power = 2.0f;
uniform int screenWidth;
uniform int screenHeight;

uniform bool enabled;

void main()
{   
	if(enabled)
	{
		// Tile noise texture over screen based on screen dimensions divided by noise size
		vec2 noiseScale = vec2(screenWidth / 4.0f, screenHeight / 4.0f);

		vec3 origin = texture(gPosition, IN.textureCoords).xyz;
		vec3 normal = texture(gNormal, IN.textureCoords).rgb;
		normal = normalize(normal);
		vec3 rvec = texture(noiseTexture, IN.textureCoords * noiseScale).xyz;

		vec3 tangent = normalize(rvec - normal * dot(rvec, normal));
		vec3 bitangent = cross(normal, tangent);
		mat3 TBN = mat3(tangent, bitangent, normal);


		float occlusion = 0.0f;
		for (int i = 0; i < kernelSize; ++i)
		{
			// Get sample position
			vec3 sample = TBN * samples[i];
			sample = origin + sample * radius;
	

			// Project sample position
			vec4 offset = vec4(sample, 1.0f);
			offset = matrices.projection * offset;
			offset.xy /= offset.w;
			offset.xy = offset.xy * 0.5f + 0.5f;

			// Get sample depth
			float sampleDepth = texture(gPosition, offset.xy).z;

			// Range check and accumulate
			float rangeCheck = smoothstep(0.0f, 1.0f, radius / abs(origin.z - sampleDepth));
			occlusion += (sampleDepth <= sample.z - 0.025 ? 1.0f : 0.0f) * rangeCheck;
		}
	
		occlusion = 1.0f - (occlusion / kernelSize);
		FragColor = pow(occlusion, power);
	}
	else
	{
		FragColor = 1.0f;
	}
}
