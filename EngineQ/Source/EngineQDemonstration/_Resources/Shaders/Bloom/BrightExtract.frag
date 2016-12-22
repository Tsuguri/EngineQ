#version 330 core

layout(location = 0) out vec4 FragColor;

in VS_DATA
{
	vec2 textureCoords;
} IN;

uniform sampler2D image;
uniform float threshold;

void main()
{             
    vec3 result = texture(image, IN.textureCoords).rgb;

    float brightness = dot(result, vec3(0.2126f, 0.7152f, 0.0722f));
    if(brightness >= threshold)
        FragColor = vec4(result, 1.0f);
	else
		FragColor = vec4(0.0f);
}