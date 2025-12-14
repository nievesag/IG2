#version 330 core

in vec4 vertex;
in vec3 normal;
in vec2 uv0;

uniform mat4 modelViewProjMat;
uniform float time;

uniform float amp;
uniform float freq;
out vec2 vUv0; 


// The idea is to move each vertex along its normal by a small, time-varying amount so the surface
// The goal is to simulate waves in the surface
void main() {

    // Texture coordinate for fragment shader
    vUv0 = uv0;
    
    // Normalized normal
    vec3 n = normalize(normal);

    // Offset (using non-equal and non-harmonically related values) -> classic plane-wave form: sin(w*t + k*x + omega)
    // sin(phase): smooth periodic motion in [-1, 1].
    // Temporal phase (w*t) controls how fast the wobble oscillates in time.
    // Spatial phase (k*x) imposes a position-dependent offset so neighboring vertices don’t move in sync
    vec3 offset = n * (amp * sin(freq * time + dot(vertex.xyz, vec3(2.0,1.7,2.3))));

    // Calculate the new position of the vertex
    vec4 pos = vec4(vertex.xyz + offset, 1.0);

    // Position in clip space
    gl_Position = modelViewProjMat * pos;

}