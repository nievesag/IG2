#version 330 core

precision mediump float;

in vec3 vNvs;
in vec3 vVvs;

uniform float rimPower;   // Rim power. Lower means wider, softer rim, while higher means tighter, sharper rim.
uniform vec3 rimColor;    // Highlight color
uniform vec3 baseColor;   // Base color

out vec4 fFragColor;

void main() {

    // Cosine of the angle between the surface normal and the view (eye) direction, then clamps it to [0, 1]
    // dot -> gives cos(theta) between N and V. ≈ 1 when the surface faces the camera (N aligned with V). ≈ 0 at the silhouette (N ⟂ V).
    float ndotv = clamp(dot(normalize(vNvs), normalize(vVvs)), 0.0, 1.0);

    // Rim effect then uses fres = pow(1.0 - ndotv, rimPower), which boosts color near the silhouette where ndotv is small.
    float fres = pow(1.0 - ndotv, rimPower);

    // Calculate final color
    vec3 col = baseColor + rimColor * fres;

    // Assign the color to the fragment
    fFragColor = vec4(col, 1.0);
}