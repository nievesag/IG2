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
    if(distance(vUv0, center) <= radius)
    {
        color = texture(texturaA, vUv0).rgb;
    }
    else
    {
        color = texture(texturaB, vUv0).rgb;
    }

    fFragColor = vec4(color, 1.0);
}