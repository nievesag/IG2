#version 330 core

uniform sampler2D texName;
uniform float flipping; // pregunta si se ha invertido el orden de los vertices (-1 invertido; 1 no invertido)

in vec2 vUv0; 

out vec4 fFragColor;

// calculos en el shader de fragmentos
void main()
{
    vec4 color = texture(texName, vUv0); // color en ese fragmento
    if (color.r > 0.6) { discard; } // si tiene mucho componente rojo -> discard

    bool frontFacing = (flipping > -1) ? gl_FrontFacing : !gl_FrontFacing; // si el fragmento es de la cara frontal

    if(frontFacing)
    {
        fFragColor = texture(texName, vUv0);
    }
    else
    {
        // !!! falta gestion de mapa de normales en el interior de la esfera
        fFragColor = vec4(0.0, 0.0, 1.0, 1.0); // lo pone naranja de momento por poner algo
    }
}