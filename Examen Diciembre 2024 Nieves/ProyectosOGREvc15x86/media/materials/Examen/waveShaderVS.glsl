#version 330 core

uniform float timeWave;
uniform vec2 centro;

in vec4 vertex;
in vec2 uv0; // Coordenadas de textura
in vec3 position;

uniform mat4 modelViewProjMat; 
out vec2 vUv0;

void main() 
{
    vec3 vertexCoord = position;

    float wavePosition = time * (size/2.0); // size = tamaño del plano

    if (vertexCoord.x >= wavePosition-20 && vertexCoord.x <= wavePosition+20)
    {
        if(wavePosition >= vertexCoord.x)
        {
            vertexCoord.y = abs(vertexCoord.x - (wavePosition-20))
        }
        else
        {
            vertexCoord.y = abs((wavePosition+20) - vertexCoord.x)
        }
    }

    vUv0 = uv0;
    gl_Position = modelViewProjMat * vertex
}
