#version 330 core

layout(location = 0) out vec4 FragColor1;
layout(location = 1) out vec4 FragColor2;

in VS_DATA
{
	vec2 textureCoords;
} IN;

uniform sampler2D image;
uniform float threshold;
uniform bool enabled;

void main()
{         
	if(enabled)
	{	
		vec3 result = texture(image, IN.textureCoords).rgb;

		float brightness = dot(result, vec3(0.2126f, 0.7152f, 0.0722f));
		if(brightness >= threshold)
			FragColor1 = FragColor2 = vec4(result, 1.0f);
		else
			FragColor1 = FragColor2 = vec4(0.0f);
	}
	else
	{
		FragColor1 = FragColor2 = vec4(0.0f);
	}
}