#version 330 core

uniform sampler2D texName;
uniform float flipping; // pregunta si se ha invertido el orden de los vertices (-1 invertido; 1 no invertido)

uniform vec3 lightAmbient;      // Intensidad de la luz ambiente
uniform vec4 lightDiffuse;      // Intensidad de la luz difusa
uniform vec4 lightPosition;     // Datos de la fuente de luz en view space
                                // lightPosition.w == 0 -> directional light
                                // lightPosition.w == 1 -> positional light
uniform vec3 materialDiffuse;   // Datos del material Front=Back


in vec2 vUv0; 

in vec3 vxNormal;
in vec3 vxVertex;

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
    // Para calcular los componentes de la luz hay dos pasos. 
    // Primero usas el componente ambiental, que te da la luz que un vertice siempre va a tener,
    // pues la luz ambiental se aplica igual a todos los vertices renderizables 
    // [IN PROGRESS] - No funciona porque no pilla bien lightAmbient.

    //Luz ambiente
    vec3 ambient = lightAmbient * materialDiffuse;


    // Despues de calcular la luz ambiental calcula la luz difusa, 
    // la cual SI depende de la posicion de la luz y orientacion del vertice.
    // Despues de calcular la difusa, se suman ambas para sacar 
    // el multiplicador de color que aporta la luz

    //Difusa (front)
    vec3 diffuse = diff(vxVertex, vxNormal) * lightDiffuse.xyz * materialDiffuse;
    vec3 vFrontColor = ambient + diffuse;

    //Difusa (back)
    diffuse = diff(vxVertex, -vxNormal) * lightDiffuse.xyz * materialDiffuse;
    vec3 vBackColor = ambient + diffuse;



    //Aplicar colores y eso

    vec3 color = texture(texName, vUv0).rgb; // color en ese fragmento
    if (color.r > 0.6) { discard; } // si tiene mucho componente rojo -> discard

    bool frontFacing = (flipping > -1) ? gl_FrontFacing : !gl_FrontFacing; // si el fragmento es de la cara frontal

    // Aplicamos cada modificador de color de la luz a ambos. 
    // Usamos el color del pixel para el frontal y la misma normal para el trasero.
    if(frontFacing)
    {
        fFragColor = vec4(color * vFrontColor, 1.0);
    }
    else
    {
        fFragColor = vec4(vxNormal * vBackColor, 1.0); 
    }
}