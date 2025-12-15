#version 330 core

uniform float timeColour;

in vec2 vUv0; // out del vs
out vec4 fFragColor;

void main()
{
    fFragColor = vec4(abs(timeColour), vUv0.x, timeColour, 1.0);
}