#version 330 core

layout(location = 0) out vec4 FragColor;

in VS_DATA
{
	vec2 textureCoords;
} IN;

uniform sampler2D ssaoInput;

void main() 
{
	vec2 texelSize = 1.0f / vec2(textureSize(ssaoInput, 0));
	
	float result = 0.0f;
	for (int x = -2; x < 2; ++x) 
	{
		for (int y = -2; y < 2; ++y) 
		{
			vec2 offset = vec2(float(x), float(y)) * texelSize;
			result += texture(ssaoInput, IN.textureCoords + offset).r;
		}
	}

    FragColor = vec4(vec3(result / (4.0f * 4.0f)), 1.0f);
}