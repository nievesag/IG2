#version 330 core

in vec4 vertex;     // Position (object space)
in vec3 normal;     // Normal (object space)
in vec2 uv0;        // Primary UVs

uniform mat4 modelViewProjMat;  // world-view-projection (for clip space)
uniform mat4 worldViewMat;      // world-view (to compute view-space position)
uniform mat3 normalMatrix;      // For transforming normals to view space

out vec3 vNormalVS;             // normal in view (camera) space
out vec3 vViewDirVS;            // View direction (from surface point to camera) in view space
out vec2 vUv0;                  // Texture coordinates

void main() {
    
    // Pass UVs straight through
    vUv0 = uv0;

    // Compute vertex position in view (camera) space
    vec3 posVS = (worldViewMat * vec4(vertex.xyz, 1.0)).xyz;

    // Camera at origin in view space
    vViewDirVS = normalize(-posVS);              

    // Normal to view space
    vNormalVS  = normalize(normalMatrix * normal); 

    // Position in clip space
    gl_Position = modelViewProjMat * vec4(vertex.xyz, 1.0);
}
