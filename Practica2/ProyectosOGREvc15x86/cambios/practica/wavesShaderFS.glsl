#version 330 core

uniform Sampler2D texName;
in vec2 Uv0;
out vec4 fFragColor;

void main()
{
    fFragColor = texture(texName, Uv0);
}