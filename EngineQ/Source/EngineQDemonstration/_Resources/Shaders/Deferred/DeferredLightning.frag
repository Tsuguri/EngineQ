#version 330 core

layout(location = 0) out vec4 color;

in VS_DATA
{
	vec2 textureCoords;
} IN;

const float ambientStrength = 0.3f;
const float specularStrength = 0.7f;
const float materialShininess = 32;

uniform sampler2D worldPosition;
uniform sampler2D normal;
uniform sampler2D albedo;

uniform float time = 0.0f;
uniform vec3 cameraPosition = vec3(1, 1, 1);
const vec3 lightDir = vec3(1, 1, 0);
const vec3 lightColor = vec3(0.5, 0.5, 0.5);

vec3 light = 3 * vec3(cos(time), 1, sin(time));

void main()
{
    vec3 colorTmp = texture(albedo, IN.textureCoords).rgb;
	float specularTmp = texture(albedo, IN.textureCoords).a;

	// Ambient
	vec3 ambient = ambientStrength * lightColor;

	// Diffuse
	vec3 norm = normalize(texture(normal, IN.textureCoords).rgb);
	vec3 dir = normalize(light);
	float diff = max(dot(norm, dir), 0.0);
	vec3 diffuse = diff * lightColor;
		

	// Specular
	vec3 viewDir = normalize(cameraPosition - texture(worldPosition, IN.textureCoords).xyz);
	vec3 halfwayDir = normalize(dir + viewDir);
	float spec = pow(max(dot(norm, halfwayDir), 0.0), materialShininess);
	vec3 specular = lightColor * spec * specularStrength * specularTmp;
	vec3 result = (ambient + diffuse + specular) * colorTmp;
	color = vec4(result, 1.0);
	//color = vec4(lightColor,1.0);
}