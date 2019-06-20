#version 330 core

in vec2 TexCoords;

uniform sampler2D woodtexture;
out vec4 color;
void main()
{
	color = texture(woodtexture, TexCoords);
}