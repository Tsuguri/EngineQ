#version 330 core

layout(location = 0)in vec3 positionIn;
layout(location = 3)in vec3 normalIn;
layout(location = 2)in vec3 colorIn;

const mat4 IdMat = mat4(1.0);

uniform mat4 ModelMat = IdMat;
uniform mat4 ViewMat = IdMat;
uniform mat4 ProjMat = IdMat;

uniform vec3 cameraPosition = vec3(1, 1, 1);
uniform vec3 lightDir = vec3(-1, -1, 0);
uniform vec3 lightColor = vec3(1, 1, 1);

uniform float time = 0.0f;
uniform float ambientStrength = 0.3f;
uniform float specularStrength = 0.1f;
uniform float materialShininess = 32;


mat4 MVP = ProjMat*ViewMat*ModelMat;
mat3 NormalMat = mat3(transpose(inverse(ModelMat)));

out vec4 position;
out vec3 normals;
out vec4 worldPosition;
out vec3 color;

void main(void)
{
	float PI=3.14;
	float A = 3.0;
	float f = 5.0 * sin(time);
	float l = 20.0;
	float w = 2.0 * PI * f;
	float k = 2.0 * PI / l;

	position = vec4(positionIn, 1.0);
	worldPosition = ModelMat*position;



	normals = NormalMat*normalIn;
	color=colorIn;
	gl_Position = MVP* vec4(
	position.x,
	position.y,
	position.z + A * sin(w * time * k + sqrt(pow(position.x, 2.0) + pow(position.y, 2.0))),0.8);
	position = ModelMat*position;
	
}