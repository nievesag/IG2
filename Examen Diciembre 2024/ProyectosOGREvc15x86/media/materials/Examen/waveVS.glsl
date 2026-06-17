#version 330 core

in vec3 position;
in vec2 uv0;

uniform mat4 modelViewProjMat;
uniform float sintime;
uniform float size;

out vec2 vUv0;

void main()
{
    vec3 vertexCoord = position;

    float xWavePos = sintime * (size/2.0);

    float xIzq = xWavePos - 40;
    float xDer = xWavePos + 40;

    if(vertexCoord.x >= xIzq && vertexCoord.x <= xDer)
    {
        if(vertexCoord.x >= xWavePos) // der
        {
            vertexCoord.y += 40 + (xWavePos - vertexCoord.x);
        }
        else // izq
        {
            vertexCoord.y += 40 - (xWavePos - vertexCoord.x);
        }
    }

    vUv0 = uv0;
    gl_Position = modelViewProjMat * vec4(vertexCoord, 1.0);
}