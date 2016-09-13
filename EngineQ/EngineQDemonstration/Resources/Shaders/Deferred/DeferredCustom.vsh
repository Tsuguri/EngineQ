#version 330 core

layout(location = 0)in vec3 positionIn;
layout(location = 3)in vec3 normalIn;
layout(location = 2)in vec3 colorIn;

out vec3 Position;
out vec3 TexCoords;//here change to vec2 when apply texture
out vec3 Normal;

out vec3 vLight;

const mat4 IdMat = mat4(1.0);

uniform mat4 ModelMat = IdMat;
uniform mat4 ViewMat = IdMat;
uniform mat4 ProjMat = IdMat;

uniform float time;

#define PI 3.14

mat4 MVP = ProjMat*ViewMat*ModelMat;
mat4 MV = ViewMat*ModelMat;
mat3 NormalMat = mat3(transpose(inverse(ModelMat)));

void main()
{
    float A = 0.03; // amplituda
	float f = 1.0; // cz.
	float l = 600.0; // dÅ‚ugoÅ›Ä‡ fali

	float w = 2.0 * PI * f; // czÄ™stoÅ›Ä‡ koÅ‚owa
	float k = 2.0 * PI / l; // liczba falowa
    

 //  Position = worldPos.xyz; 
  //  gl_Position = ProjMat * ViewMat * worldPos;
  //  TexCoords = colorIn;

 //   Normal = NormalMat * normalIn;





	vLight = normalize((vec4(0.5, 0.5, 1.0, 1.0) * MV).xyz);
	Normal = NormalMat* normalIn; // przekazujemy wektory normalne fragment shaderowi
    vec4 worldPos = ModelMat * vec4(positionIn, 1.0f);
	Position = worldPos.xyz; // przekazujemy pozycjÄ™ fragment shaderowi
		
	gl_Position = MVP
				* vec4(
					positionIn.x + A * sin(w * time - k * (positionIn.y + positionIn.z)),
					positionIn.y + A * sin(w * time - k * (positionIn.x + positionIn.z)),
					positionIn.z + A * sin(w * time - k * (positionIn.x + positionIn.y)),
				1.0);

}  