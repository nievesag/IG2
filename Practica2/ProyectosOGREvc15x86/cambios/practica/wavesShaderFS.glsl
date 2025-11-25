#version 330 core

uniform sampler2D texName;
in vec2 vTexCoorVS;
out vec4 fFragColor;

void main()
{
    fFragColor = texture(texName, vTexCoorVS); 
}