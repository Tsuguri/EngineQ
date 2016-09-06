#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D scene;
uniform sampler2D bloomBlur;
uniform float exposure = 4.0;

void main()
{             
    const float gamma = 2.2;
    vec3 hdrColor = texture(scene, TexCoords).rgb;      
    vec3 bloomColor = texture(bloomBlur, TexCoords).rgb;
   	vec3 result;

   	result=bloomColor+hdrColor;

    // tone mapping
   // vec3 result = hdrColor;//place for exposure tone mapping
    // also gamma correct while we're at it       
   // result = pow(result, vec3(1.0 / gamma));

    FragColor = vec4(result, 1.0f);
}