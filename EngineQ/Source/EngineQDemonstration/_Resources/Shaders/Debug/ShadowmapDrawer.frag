#version 330 core

layout(location = 0) out vec4 FragColor;

in VS_DATA
{
	vec2 textureCoords;
} IN;

const int MaxLights = 4;

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	mat4 lightMatrix;

	float distance;
	
	bool castsShadows;
	float farPlane;
};

uniform Light lights[MaxLights];
uniform int lightCount;

uniform sampler2D image;

uniform sampler2D lights_q_0_q_DirectionalShadowMap;
uniform sampler2D lights_q_1_q_DirectionalShadowMap;
uniform sampler2D lights_q_2_q_DirectionalShadowMap;
uniform sampler2D lights_q_3_q_DirectionalShadowMap;

uniform samplerCube lights_q_0_q_PointShadowMap;
uniform samplerCube lights_q_1_q_PointShadowMap;
uniform samplerCube lights_q_2_q_PointShadowMap;
uniform samplerCube lights_q_3_q_PointShadowMap;

void main()
{             
	float color = texture(lights_q_0_q_DirectionalShadowMap, IN.textureCoords).x;

	FragColor = vec4(vec3(color), 1.0f);
}
