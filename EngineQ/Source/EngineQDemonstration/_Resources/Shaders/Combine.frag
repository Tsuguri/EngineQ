#version 330 core

layout(location = 0) out vec4 FragColor;

in VS_DATA
{
	vec2 textureCoords;
} IN;

uniform sampler2D scene;
uniform sampler2D bloom;
uniform sampler2D ssao;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gColor;

uniform float exposure = 1.1f;
uniform float gamma = 2.2f;

uniform int drawImage = 0;

#include "Common/Matrices.shh"

void main()
{
	switch (drawImage)
	{
		// Full
		case 0:
			{
				vec3 hdrColor = texture(scene, IN.textureCoords).rgb;
				vec3 bloomColor = texture(bloom, IN.textureCoords).rgb;
   
				vec3 combined = bloomColor + hdrColor;

				vec3 result = vec3(1.0f) - exp(-combined * exposure);
				result = pow(result, vec3(1.0f / gamma));

				FragColor = vec4(result, 1.0f);
			}
			break;

		// Scene
		case 1:
			{
				FragColor = vec4(texture(scene, IN.textureCoords).rgb, 1.0f);
			}
			break;

		// Bright
		case 2:
			{
				FragColor = vec4(texture(bloom, IN.textureCoords).rgb, 1.0f);
			}
			break;

		// SSAO
		case 3:
			{
				FragColor = vec4(vec3(texture(ssao, IN.textureCoords).r), 1.0f);
			}
			break;

		// G-Position
		case 4:
			{
				vec3 pos = texture(gPosition, IN.textureCoords).xyz;
				pos = (inverse(matrices.view) * vec4(pos, 1.0f)).xyz;

				FragColor = vec4(pos, 1.0f);
			}
			break;

		// G-Normal
		case 5:
			{
				vec3 norm = texture(gNormal, IN.textureCoords).xyz;
				norm = normalize(mat3(transpose(matrices.view)) * norm);

				FragColor = vec4(norm, 1.0f);
			}
			break;

		// G-Color
		case 6:
			{
				FragColor = vec4(texture(gColor, IN.textureCoords).xyz, 1.0f);
			}
			break;
	}
}
