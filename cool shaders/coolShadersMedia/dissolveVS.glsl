#version 330 core

in vec4 vertex;
in vec2 uv0;

uniform mat4 modelViewProjMat;

out vec2 vUV;

void main() {
    vUV = uv0;
    gl_Position = modelViewProjMat * vec4(vertex.xyz, 1.0);    
}