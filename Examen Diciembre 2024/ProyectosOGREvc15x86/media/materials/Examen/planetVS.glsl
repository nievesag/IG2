#version 330 core

in vec3 position;
in vec2 uv0;

uniform mat4 modelViewProjMat;

out vec2 vUv0;

void main()
{
    vec3 vertexCoord = position;

    vUv0 = uv0;
    gl_Position = modelViewProjMat * vec4(vertexCoord, 1.0);
}