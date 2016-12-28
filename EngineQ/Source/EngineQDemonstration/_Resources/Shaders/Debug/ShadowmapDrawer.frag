#version 330 core

layout(location = 0) out vec4 FragColor;

in VS_DATA
{
	vec2 textureCoords;
} IN;

//#include "../Common/Light.shh"

uniform sampler2D backDepth;
uniform sampler2D frontDepth;
uniform sampler2D depthMap;

uniform sampler2D light0backVolumeMap;
uniform sampler2D light0frontVolumeMap;
uniform sampler2D lights_q_0_q_DirectionalShadowMap;

uniform int mode;

float LinearizeDepth(float depth)
{
//	const float near_plane = 0.01f;
//	const float far_plane = 100.0f;
	const float near_plane = 0.01f;
	const float far_plane = 100.0f;

    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane)) / (far_plane - near_plane);
}

void main()
{             
	float color = 0.0f;
	
	switch(mode)
	{
		case 0:
	//	color = texture(frontDepth, IN.textureCoords).x;
		color = texture(light0frontVolumeMap, IN.textureCoords).x;
		break;

		case 1:
	//	color = texture(backDepth, IN.textureCoords).x;
		color = texture(light0backVolumeMap, IN.textureCoords).x;
		break;

		case 2:
	//	color = texture(depthMap, IN.textureCoords).x;
		color = texture(lights_q_0_q_DirectionalShadowMap, IN.textureCoords).x;
		break;
	}

//	FragColor = vec4(vec3(LinearizeDepth(color)), 1.0f);
	FragColor = vec4(vec3(color), 1.0f);
} 
