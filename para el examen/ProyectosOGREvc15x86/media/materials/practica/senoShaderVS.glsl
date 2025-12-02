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
    gl_position = modelViewProjMat * vertexCoord;

/*
    vec3 vertexCoord = position;

    float distanceCenter = length(vertexCoord.xz - cent); 

    float a = 10.0f; // lo rapido que va
    float b = 2.0f;  // lo alto que sube

    vertexCoord.y += sin(vertexCoord.x + (timeWave*a)) * b + sin(vertexCoord.z + (distanceCenter) + (timeWave*a)) * b;

    vTexCoorVS = uv0;

    gl_Position = modelViewProjMat * vec4(vertexCoord, 1.0);
    */
}