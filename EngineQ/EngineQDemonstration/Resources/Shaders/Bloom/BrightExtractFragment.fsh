#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D image;

void main()
{             
    vec3 result = texture(image, TexCoords).rgb;

    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 0.75)
        FragColor = vec4(result, 1.0);
}