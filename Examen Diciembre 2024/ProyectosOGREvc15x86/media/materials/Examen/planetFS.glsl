#version 330 core

in vec2 vUv0;

uniform sampler2D textura;
uniform float sintime;

out vec4 fFragColor;

void main() 
{
    //vec3 color = vec3(texture(textura, vUv0));

    vec3 color = vec3(abs(sintime), vUv0.t, sintime);

    fFragColor = vec4(color, 1.0);
}