#version 330 core

in vec4 vertex;
in vec3 normal;

uniform mat4 modelViewProjMat;
uniform mat3 normalMatrix;      

out vec3 vNvs;                  // Normal in view space

void main() {
    
    // Transform normal to view space for lighting in the fragment shader
    vNvs = normalize(normalMatrix * normal);

    // Position in clip space
    gl_Position = modelViewProjMat * vec4(vertex.xyz, 1.0);
}