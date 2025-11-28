#version 330 core

uniform mat4 modelViewProjMat;
uniform float timeWave;
uniform vec2 cent;

in vec2 uv0;
in vec3 position;

out vec2 vTexCoorVS; // se lo pasa a FS

void main()
{
    vec3 vertexCoord = position;

    float distanceCenter = length(vertexCoord.xz - cent); 

    float a = 10.0f; // lo rapido que va
    float b = 2.0f;  // lo alto que sube

    vertexCoord.y += sin(vertexCoord.x + (timeWave*a)) * b + sin(vertexCoord.z + (distanceCenter) + (timeWave*a)) * b;

    vTexCoorVS = uv0;

    gl_Position = modelViewProjMat * vec4(vertexCoord, 1.0);
}