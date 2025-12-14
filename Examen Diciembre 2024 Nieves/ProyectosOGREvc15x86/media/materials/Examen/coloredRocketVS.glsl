#version 330 core

uniform mat4 modelViewProjMat;

in vec2 uv0; // Coordenadas de textura
in vec3 position;

out vec2 vUv0;

void main()
{
    vec3 vertexCoord = position;
    gl_Position = modelViewProjMat * vec4(vertexCoord, 1.0);
}