#version 330 core

uniform mat4 modelViewProjMat;
uniform float time;

in vec2 uv0;
in vec3 position;

out vec2 vTexCoorVS;

void main()
{
    vec3 vertexCoord = position;

    vec3 center = vec3(0.0,0.0,0.0);
    float distanceCenter = length(vertexCoord.xz - center.xz); 

    float a = 10.0f;
    float b = 1.0f;

    vertexCoord.y += sin(vertexCoord.x + (time*a)) * b + sin(vertexCoord.z + (distanceCenter) + (time*a)) * b;

    vTexCoorVS = uv0;

    gl_Position = modelViewProjMat * vec4(vertexCoord, 1.0);
}