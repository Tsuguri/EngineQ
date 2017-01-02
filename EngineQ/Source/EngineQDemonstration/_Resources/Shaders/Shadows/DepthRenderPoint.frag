#version 330 core

in vec3 pos;

uniform vec3 lightPosition;
uniform float farPlane;

out float FragColor;
void main()
{
    float lightDistance = length(pos.xyz - lightPosition);

	FragColor = lightDistance;
}