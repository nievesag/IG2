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

    wavePosition = time * (size/2.0); // size = tamaño del plano

    if(vertexCoord.x >= wavePosition-20 && vertexCoord.x <= wavePosition+20)
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

    vTexCoorVS = uv0;
    gl_Position = modelViewProjMat * vertexCoord;
}