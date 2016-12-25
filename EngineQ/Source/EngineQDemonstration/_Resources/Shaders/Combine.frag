#version 330 core

layout(location = 0) out vec4 FragColor;

in VS_DATA
{
	vec2 textureCoords;
} IN;

uniform sampler2D scene;
uniform sampler2D bloom;

const float exposure = 4.1f;
const float gamma = 2.2f;

void main()
{             
    vec3 hdrColor = texture(scene, IN.textureCoords).rgb;      
    vec3 bloomColor = texture(bloom, IN.textureCoords).rgb;
   
   	vec3 combined = bloomColor + hdrColor;

	vec3 result = vec3(1.0f) - exp(-combined * exposure);
	result = pow(result, vec3(1.0f / gamma));

    FragColor = vec4(result, 1.0f);
}
