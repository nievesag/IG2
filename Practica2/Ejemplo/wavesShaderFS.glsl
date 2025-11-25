//Fragment shader se encarga del color

//uniform son definidas en el.material no se pueden modificar en el .glsl, out de salida, in de entrada y hay de entrada/salida
//con out puedo enviar variables y si pej el vertex los envia, el fragment con in puede recogerlo

uniform sampler2D waterTex;
out vec4 fragColor; //out pq lo envia para que la cpu reciba el color
in vec2 vTexCoorVS; //cordenada recibida del VS para cargar la textura en cada coord


//creacion del main

void main()
{
 fragColor= texture(waterTex, vTexCoorVS); //nos guardamos el color de la textura que es la textura
//no hace falta hacer gl_FragCoord solo si quisiera un degradado o algo parecido
}