#version 330 core

in vec4 position;
in vec3 normals;
in vec4 worldPosition;
in vec3 color;

#include "BasicCommon.shh"

//uniform float myRandomValue = 1.0f;

out vec4 ColorOut;

void main(void)
{
vec3 colorTmp;

		colorTmp=color;

		if(worldPosition.x>1)
		colorTmp=vec3(1.0f);

	//ambient
		vec3 ambient = ambientStrength*lightColor;

	//diffuse
		vec3 norm = normalize(normals);
		vec3 dir = normalize(lightDir);
		float diff = max(dot(norm, dir), 0.0);
		vec3 diffuse = diff * lightColor;

	//specular
		vec3 viewDir = normalize(cameraPosition - worldPosition.xyz);
		vec3 halfwayDir = normalize(dir + viewDir);
		float spec = pow(max(dot(norm, halfwayDir), 0.0), materialShininess) * specularStrength;
		vec3 specular = lightColor * spec;
		vec3 result = (ambient+diffuse+specular)*colorTmp;
		ColorOut=vec4(result,1.0);
		//ColorOut=vec4(vec3(result.xy, result.z * myRandomValue),1.0);
}