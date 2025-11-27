#version 330 core

uniform sampler2D texName;
uniform float flipping; // pregunta si se ha invertido el orden de los vertices (-1 invertido; 1 no invertido)

in vec2 vUv0; 
in vec3 vNormal;
in vec3 vLightDirection;
in vec3 vLightAmbient;
in vec3 vLightDiffuse;
in vec3 vMaterialDiffuse;

out vec4 fFragColor;

// calculos en el shader de fragmentos
void main()
{
    bool frontFacing = (flipping > -1) ? gl_FrontFacing : !gl_FrontFacing; // si el fragmento es de la cara frontal

    vec3 color = vec3(texture(texName, vUv0)); // color en ese fragmento
    if (color.r > 0.6) { discard; } // si tiene mucho componente rojo -> discard

    vec3 ambient = vLightAmbient*vMaterialDiffuse;
    vec3 diffuse;
    
    if(frontFacing)
    {
        diffuse = max(0, dot(vNormal, -vLightDirection))*vLightDiffuse*vMaterialDiffuse;
        //fFragColor = texture(texName, vUv0);
    }
    else
    {
        color = -vNormal;
        diffuse = max(0, dot(-vNormal, -vLightDirection))*vLightDiffuse*vMaterialDiffuse;

        // !!! falta gestion de mapa de normales en el interior de la esfera
        //fFragColor = vec4(0.0, 0.0, 1.0, 1.0); // lo pone naranja de momento por poner algo
    }

    color = color * (ambient + diffuse);
    fFragColor = vec4(color,1.0);
}