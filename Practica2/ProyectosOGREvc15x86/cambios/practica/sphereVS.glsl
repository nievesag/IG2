#version 330 core

uniform mat4 modelViewMat;
uniform mat4 modelViewProjMat;
uniform mat4 normalMat;

in vec4 vertex; 
in vec3 normal;
in vec2 uv0;

out vec2 vUv0;
out vec3 vxNormal;
out vec3 vxVertex;

void main()
{
    // Hacemos unos calculos rapidos para pasarle
    // solo la informacion necesaria al FS
    vec3 viewVertex = vec3(modelViewMat * vertex); 
    vec3 viewNormal = normalize(normal);

    vUv0 = uv0; 
    vxNormal = viewNormal;
    vxVertex = viewVertex;
    gl_Position = modelViewProjMat * vertex;
}