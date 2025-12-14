#version 330 core

uniform sampler2D texName;
in vec2 vUv0; // out del vs
out vec4 fFragColor;

void main() 
{
    fFragColor = texture(texName, vUv0); 
}
