#version 330 core

uniform mat4 modelViewProjMat;
uniform vec3 lightDirection;
uniform vec3 lightDiffuse;
uniform vec3 lightAmbient;
uniform vec3 materialDiffuse;

in vec4 vertex; 
in vec2 uv0;
in vec3 normal;

out vec2 vUv0;
out vec3 vNormal;
out vec3 vLightDirection;
out vec3 vLightDiffuse;
out vec3 vLightAmbient;
out vec3 vMaterialDiffuse;

void main()
{
    vUv0 = uv0; 
    vNormal = normal;
    vLightDirection = lightDirection;
    vLightDiffuse = lightDiffuse;
    vLightAmbient = lightAmbient;
    vMaterialDiffuse = materialDiffuse;
    gl_Position = modelViewProjMat * vertex;
}