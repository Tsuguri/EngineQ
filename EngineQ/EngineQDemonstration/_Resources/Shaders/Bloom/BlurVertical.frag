#version 330 core

layout(location = 0) out vec4 FragColor;

in VS_DATA
{
	vec2 textureCoords;
} IN;

uniform sampler2D image;

const int WeightsSize = 5;
const float Weights[WeightsSize] = float[]( 0.227027f, 0.1945946f, 0.1216216f, 0.054054f, 0.016216f );

void main()
{             
    vec2 tex_offset = 1.0f / textureSize(image, 0); // gets size of single texel
    vec3 result = texture(image, IN.textureCoords).rgb * Weights[0]; // current fragment's contribution

    for(int i = 1; i < WeightsSize; ++i)
    {
        result += texture(image, IN.textureCoords + vec2(0.0f, tex_offset.y * i)).rgb * Weights[i];
        result += texture(image, IN.textureCoords - vec2(0.0f, tex_offset.y * i)).rgb * Weights[i];
    }

    FragColor = vec4(result, 1.0f);
}