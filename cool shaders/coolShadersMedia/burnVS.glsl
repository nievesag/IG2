#version 330 core

in vec4 vertex;   // Position (object space)
in vec3 normal;   // Normal (object space)
in vec2 uv0;      // Primary texture coordinatesVs

uniform mat4 modelViewProjMat; // To calculate clip space

out vec2 vUv0;                  // Texture coordinates

void main() {
    
    // Texture coordinates for fragment shader
    vUv0 = uv0;

    // Position in clip space
    gl_Position = modelViewProjMat * vec4(vertex.xyz, 1.0);
}