#version 330 core

in vec4 vertex;
in vec2 uv0; // Coordenadas de textura

uniform float costime;
uniform float sintime;

uniform mat4 modelViewProjMat;

out vec2 vUv0;
out vec2 vUv1;

void main()
{
    vUv0 = vec2(uv0.s * cos(30) - uv0.t * sin(30), uv0.s * sin(30) + uv0.t * cos(30));

    //vUv0 = uv0;
    //vUv1 = uv0;

    gl_Position = modelViewProjMat * vertex;
}