#version 330 core

in vec4 position;
in vec3 normals;
in vec4 worldPosition;
in vec3 color;

uniform vec3 cameraPosition = vec3(1, 1, 1);
uniform vec3 lightDir = vec3(-1, -1, 0);
uniform vec3 lightColor = vec3(1,1,1);
uniform float ambientStrength=0.3f;
uniform float specularStrength=0.1f;
uniform float materialShininess=32;

out vec4 ColorOut;

void main(void)
{
vec3 colorTmp;

		colorTmp=color;
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
		float spec = pow(max(dot(norm, halfwayDir), 0.0), materialShininess);
		vec3 specular = lightColor * spec;
		vec3 result = (ambient+diffuse+specular)*colorTmp;
		ColorOut=vec4(result,1.0);
}




		uniform float time;
		varying vec3 vLight;
		varying vec3 vNormal;
		varying vec3 vPosition;

		void main() {
			float dotProduct = clamp(dot(vLight, vNormal), 0.0, 1.0);
			vec3 red = vec3(1.0, 0.0, 0.0);
			vec3 white = vec3(1.0);
			vec3 black = vec3(0.0);

			if (abs(vPosition.y) < 1.0)
				gl_FragColor = vec4(black * dotProduct, 1.0);
			else if (vPosition.y < 0.0)
				gl_FragColor = vec4(white * dotProduct, 1.0);
			else
				gl_FragColor = vec4(red * dotProduct, 1.0);

			if (vPosition.z > 0.0)
			{
				float r2 = pow(vPosition.x, 2.0) + pow(vPosition.y, 2.0);

				if (r2 < pow(4.775, 2.0))
					gl_FragColor = vec4(black * dotProduct, 1.0);
				if (r2 < pow(4.0, 2.0))
					gl_FragColor =  vec4(white * dotProduct, 1.0);
				if (r2 < pow(2.5, 2.0))
					gl_FragColor =  vec4(black * dotProduct, 1.0);
				if (r2 < pow(1.75, 2.0))
					gl_FragColor =  vec4(white * dotProduct, 1.0);
			}
		}