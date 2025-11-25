//vertex shader se encarga de las coordenadas

//uniform son definidas en el.material no se pueden modificar en el .glsl, out de salida, in de entrada y hay de entrada/salida
//con out puedo enviar variables y si pej el vertex los envia, el fragment con in puede recogerlo 

uniform mat4 modelViewProjMat; 
uniform float time;

in vec3 position; //recogo con in la posicion del vertice del mesh
out vec2 vTexCoorVS; //la coordenada que voy a enviar
in vec2 uv0; //coordenada inicial de textura


//creacion del main

void main()
{
 //si esta dentro del main las variables que me cree, son aux por lo que no van a tener in,out,uniform

 vec3 vertexCoord = position;

vec3 center= vec3(0.0,0.0,0.0);
float distanceCenter = length(vertexCoord.xz - center.xz); //lenght para  tener el modulo y .xz para no tener encuneta la altura


float a= 30.0f; //frquencia
float b= 0.5f; //amplitud

vertexCoord.y += sin(vertexCoord.x + (time*a)) * b + sin(vertexCoord.z + (distanceCenter) + (time*a)) * b;

vTexCoorVS= uv0;


//donde dibuja en pantalla
gl_Position = modelViewProjMat * vec4(vertexCoord, 1.0);//hay que transformar la coordenada de vertice xyz a xyzw pq la de proyeccion es de 4*4
}