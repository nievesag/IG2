#version 330 core
#include <math.h>

in vec2 Uv0;
in vec4 vertex;

uniform mat4 modelViewProjMat;
uniform float waveTime;
uniform vec3 coor;

uniform float a;
uniform float b;

out vec2 Uv0;

void main()
{
    float distanceCenter = sqrt(pow((vertex.x-coor.x), 2) + pow((vertex.y-coor.y), 2) + pow((vertex.z-coor.z), 2));
    vertex.y += sin(vertex.x + (waveTime*a)) * b + sin(vertex.z + (distanceCenter) + (waveTime*a)) * b;

    gl_Position = vertex;

    Uv0 = uv0;
}