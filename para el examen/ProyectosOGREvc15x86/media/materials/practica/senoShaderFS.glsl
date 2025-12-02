#version 330 core

uniform sampler2D texName;
in vec2 vTexCoorVS; // lo recibe desde VS
out vec4 fFragColor;

void main()
{
    fFragColor = texture(texName, vTexCoorVS); 
}