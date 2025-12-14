#version 330 core

in vec2 vUV;

uniform sampler2D texture0;  // Texture (corrosion.jpg)
uniform float timeVal;       // Time
uniform float speed;         // Dissolve speed
uniform float threshold;     // Base threshold
uniform float softness;      // Edge softness
uniform vec3  tint;          // Color tint

out vec4 fFragColor;

// Cheap hash noise from UV. 
float uvNoise(vec2 uv) {

    // Values used here are effectively seeds (non-harmonically related numbers reduces visible banding/patterns)
    vec2 n = vec2(dot(uv, vec2(127.1, 311.7)), dot(uv, vec2(269.5, 183.3)));

    // The constant is a “magic” hash constant used to decorrelate the value before taking fract
    // -> Non-integer, not a simple multiple of π, and large enough to avoid visible repeats
    // The idea is to produce a pseudo-random number uniformly mapped to [0,1) -> fract(x) = x − floor(x)
    return fract(sin(n.x + n.y) * 43758.5453);
}


// General idea: As timeVal increases, sin(timeVal) changes cut. 
// When cut goes up, the boundary (cut - softness) goes up, so a larger portion of noise values n falls below it.
void main() {
    
    // Scroll UV over time for movement. 2*pi turns speed into cycles-per-second and converts time into an angular phase for sin/cos.
    float t = timeVal * speed * 6.2831853;

    // 0.15 is the horizontal (U) radius and 0.10 is the vertical (V) radius of an elliptical motion. 
    // Values are in normalized UV units, so 0.15 ≈ 15% of the texture width, 0.10 ≈ 10% of the height
    vec2 uv = vUV + vec2(0.15 * cos(t), 0.10 * sin(t));

    // Get the color from the texture
    vec3 albedo = texture(texture0, uv).rgb;

    // Applies uvNoise
    float n = uvNoise(uv * 8.0);
    float anim = 0.5 + 0.5 * sin(t);    // Normalize
    float cut = clamp(threshold + 0.4 * (anim - 0.5), 0.0, 1.0);

    // Soft dissolve edge
    // n << cut -> edge approx. 0 (fully dissolved); n >> cut -> edge aprox. 1 (fully visible)
    // In between, smoothstep feathers over a width of 2*softness.
    float edge = smoothstep(cut - softness, cut + softness, n);
    
    if (edge <= 0.001) 
        discard;

    // Final color for the fragment
    vec3 c = albedo * tint * edge;
    fFragColor = vec4(c, 1.0);
}