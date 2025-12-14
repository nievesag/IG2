#version 330 core

in vec4 vertex;
in vec3 normal;
in vec2 uv0;

uniform mat4 modelViewProjMat;
uniform mat4 worldViewMat;
uniform mat3 normalMatrix;

out vec3 vNvs;
out vec3 vVvs;

void main() {
    
    // Position in view space
    vec3 posVS = (worldViewMat * vec4(vertex.xyz, 1.0)).xyz;

    // Direction from the vertex to the camera
    vVvs = normalize(-posVS);
    
    // Normal in view space
    vNvs = normalize(normalMatrix * normal);

    // Vertex in clip space
    gl_Position = modelViewProjMat * vec4(vertex.xyz, 1.0);
}