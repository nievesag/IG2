#version 330 core

out vec4 fFragColor;

uniform float varColor;

in vec2 vUv0; // out del vs

void main() 
{
    float r = 0.2;

    vec2 c1 = vec2(0.0, 0.5);
    vec2 c2 = vec2(0.5, 0.5);
    vec2 c3 = vec2(1.0, 0.5);

    if(distance(vUv0, c1) <= r || distance(vUv0, c2) <= r || distance(vUv0, c3) <= r)
    {
        discard;
    }

    vec3 color = vec3(varColor, varColor, varColor);

    fFragColor = vec4(color, 1.0);
}