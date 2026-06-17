#version 330 core

in vec2 vUv0;
in vec3 vxNormal;
in vec3 vxVertex;

uniform float sintime;
uniform float Flipping;
uniform vec4 lightDiffuse;      // Intensidad de la luz difusa
uniform vec4 lightPosition;     // Datos de la fuente de luz en view space
                                // lightPosition.w == 0 -> directional light
                                // lightPosition.w == 1 -> positional light
uniform vec3 materialDiffuse;   // Datos del material Front=Back

out vec4 fFragColor;

// Calcula el porcentaje de iluminacion de cada vertice usando la normal y la direccion de la luz
float diff(vec3 cVertex, vec3 cNormal)
{
    vec3 lightDir = lightPosition.xyz;

    if(lightPosition.w == 1)
        lightDir = lightPosition.xyz - cVertex;

    return max(dot(cNormal, normalize(lightDir)), 0.0);
}

void main() 
{
    if (vUv0.t < 0.3 || vUv0.t > 0.7)
    {
        discard;
    }

    // Para calcular los componentes de la luz hay dos pasos. 
    // Primero usas el componente ambiental, que te da la luz que un vertice siempre va a tener,
    // pues la luz ambiental se aplica igual a todos los vertices renderizables 

    // Despues de calcular la luz ambiental calcula la luz difusa, 
    // la cual SI depende de la posicion de la luz y orientacion del vertice.
    // Despues de calcular la difusa, se suman ambas para sacar 
    // el multiplicador de color que aporta la luz

    //Difusa (front)
    vec3 diffuse = diff(vxVertex, vxNormal) * lightDiffuse.xyz * materialDiffuse;
    vec3 vFrontColor = diffuse;

    //Difusa (back)
    diffuse = diff(vxVertex, -vxNormal) * lightDiffuse.xyz * materialDiffuse;
    vec3 vBackColor = diffuse;

    bool frontFacing = (Flipping > -1)? gl_FrontFacing : !gl_FrontFacing;

    vec3 color;

    if (frontFacing)
        color = vec3(sintime, sintime, sintime);
    else
        color = vec3(-vxNormal * vBackColor);

    fFragColor = vec4(color, 1.0);
}