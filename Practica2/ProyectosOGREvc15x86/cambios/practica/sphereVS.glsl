#version 330 core

uniform mat4 modelViewProjMat;

in vec4 vertex; 
in vec2 uv0;

out vec2 vUv0;

void main()
{
    vUv0 = uv0; 
    gl_Position = modelViewProjMat * vertex;
}