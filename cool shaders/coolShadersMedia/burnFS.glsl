#version 330 core

in vec2 vUv0;

uniform sampler2D noiseTex;     // Texture
uniform float threshold;        // 0..1, animated
uniform vec3 edgeColor;         // Edge color

out vec4 fFragColor;

void main() {

    // Get the red component
    float n = texture(noiseTex, vUv0).r;

    // Discard fragment
    if (n < threshold) 
        discard; 

    // Produces a soft ramp around the threshold band. n << threshold: m aprox. 0; n >> threshold: m aprox. 1
    // In a 0.02 band around threshold, m transitions smoothly 0->1
    float m = smoothstep(threshold - 0.02, threshold + 0.02, n);

    // Calculate edge color, which increases in values near the threshold. 
    // Multiply by different values to see different brigth effects (5 in this case)
    vec3 edge = edgeColor * (1.0 - m) * 5.0; 
        
    // Final color
    fFragColor = vec4(edge, 1.0);
}