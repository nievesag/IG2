#version 330 core

uniform vec4 color;

in vec2 vUv0; // out del vs

out vec4 fFragColor;

uniform sampler2D texturaA;
uniform sampler2D texturaB;
uniform float radius;

void main()
{
    vec2 center = vec2(0.5, 0.5);

    vec3 color;
    vec3 black = vec3(0.0, 0.0, 0.0);
    if(texture(texturaB, vUv0).rgb == black)
    {
        color = texture(texturaB, vUv0).rgb;
    }
    else
    {
        color = texture(texturaA, vUv0).rgb;
    }

    fFragColor = vec4(color, 1.0);
}