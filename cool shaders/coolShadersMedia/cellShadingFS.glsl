#version 330 core

in vec3 vNvs;                                   // Normal in VS

uniform vec3 lightDirVS;                        // Light direction in VS
uniform vec3 shade0, shade1, shade2, shade3;    // Shades
uniform float edgeThreshold;                    // Edge darkening via rim

out vec4 fFragColor;

void main() {

    // Normalized normal
    vec3 N = normalize(vNvs);
    
    // Use surface-to-light vector for Lambert; Remember that OGRE auto param is light's shining direction
    vec3 L = normalize(-lightDirVS);
    float ndotl = clamp(dot(N, L), 0.0, 1.0);

    // 4-band quantization
    float s = ndotl;

    // Discretize the final color using the Lambert term
    vec3 c =
        (s < 0.25) ? shade0 :
        (s < 0.50) ? shade1 :
        (s < 0.75) ? shade2 : shade3;

    // Extra edge darkening (simple rim). smoothstep remaps x into [0, 1] between edge0 and edge1, then applies a smooth cubic curve
    // ndotl is largest near silhouettes, (where the light is perpendicular to the normal), so rim grows toward edges.
    float rim = smoothstep(0.0, edgeThreshold, 1.0 - ndotl);
    c *= mix(1.0, 0.6, rim);

    // Final colot for the fragment
    fFragColor = vec4(c, 1.0);
}