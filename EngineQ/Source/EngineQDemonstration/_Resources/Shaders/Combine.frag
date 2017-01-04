#version 330 core

layout(location = 0) out vec4 FragColor;

in VS_DATA
{
	vec2 textureCoords;
} IN;

uniform sampler2D scene;
uniform sampler2D bloom;
uniform sampler2D ssao;

uniform float exposure = 1.1f;
uniform float gamma = 2.2f;

uniform int drawImage = 0;

void main()
{
	switch (drawImage)
	{
		// Normal
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

		// SSAO
		case 1:
			{
				FragColor = vec4(vec3(texture(ssao, IN.textureCoords).r), 1.0f);
			}
			break;
	}
}
