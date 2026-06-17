#version 330 core

uniform mat4 modelViewProjMat; 
uniform float timeWave;
uniform float size;

in vec2 uv0; // Coordenadas de textura
in vec3 position;

out vec2 vUv0;

float wavePosition = 1500;

void main() 
{
    vec3 vertexCoord = position;

    wavePosition = timeWave * (size/2.0); // size = tamaño del plano

    if (vertexCoord.x >= wavePosition-20 && vertexCoord.x <= wavePosition+20)
    {
        if(wavePosition >= vertexCoord.x)
        {
            vertexCoord.y = abs(vertexCoord.x - (wavePosition-20));
        }
        else
        {
            vertexCoord.y = abs((wavePosition+20) - vertexCoord.x);
        }
    }

    vUv0 = uv0;
    gl_Position = modelViewProjMat * vec4(vertexCoord, 1.0);
}