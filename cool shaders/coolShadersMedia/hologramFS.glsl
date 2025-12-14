#version 330 core

in vec3 vNormalVS;
in vec3 vViewDirVS;
in vec2 vUv0;

uniform vec3 holoColor;         // Color for the hologram
uniform float time;             // Time
uniform float lineDensity;      // Lines per UV unit
uniform float lineScroll;       // Scroll speed 

out vec4 fFragColor;

void main() {
    
    // Fresnel -> pow(1 − max(dot(N, V), 0), 2)
    // High near silhouettes where the view is perpendicular to the surface normal
    float fres = pow(1.0 - max(dot(normalize(vNormalVS), normalize(vViewDirVS)), 0.0), 2.0);

    // Lines (in range [0 - 1] ) Horizontal bands along U with frequency
    // 1 at the bright center of a line, 0 in the dark gap
    float lines = 0.5 + 0.5 * sin(vUv0.y * lineDensity + time * lineScroll);

    // Intensity of current fragment
    float intensity = clamp(fres * lines, 0.0, 1.0);

    // Final color using a semi-transparent alpha (0.8)
    fFragColor = vec4(holoColor * intensity, 0.8);
}
