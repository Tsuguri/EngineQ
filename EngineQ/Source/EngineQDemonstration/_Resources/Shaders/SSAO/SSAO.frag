#version 330 core

layout(location = 0) out float FragColor;

in VS_DATA
{
	vec2 textureCoords;
} IN;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D noiseTexture;

const int kernelSize = 64;
const float radius = 1.0f;
const float power = 4.0f;

uniform vec3 samples[kernelSize];
uniform mat4 projection;

uniform int screenWidth;
uniform int screenHeight;

void main()
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
	for(int i = 0; i < kernelSize; ++i)
	{
		// Get sample position
		vec3 sample = TBN * samples[i];
		sample = origin + sample * radius;
	

		// Project sample position
		vec4 offset = vec4(sample, 1.0f);
		offset = projection * offset;
		offset.xy /= offset.w;
		offset.xy = offset.xy * 0.5f + 0.5f;

		// Get sample depth
		float sampleDepth = texture(gPosition, offset.xy).z;

		// Range check and accumulate
		float rangeCheck = smoothstep(0.0f, 1.0f, radius / abs(origin.z - sampleDepth));
		occlusion += (sampleDepth <= sample.z ? 1.0f : 0.0f) * rangeCheck;
	}
	
	occlusion = 1.0f - (occlusion / kernelSize);
	FragColor = pow(occlusion, power);
}
