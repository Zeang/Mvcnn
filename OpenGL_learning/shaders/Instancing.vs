#version 330 core


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;
out vec3 fColor;
out vec3 viewPos;

uniform mat4 projection;
uniform mat4 view;

uniform mat4 trans;
uniform vec3 color;

void main()
{
	
	
	gl_Position = projection * view * trans * vec4(position, 1.0f);
	FragPos = vec3(trans * vec4(position, 1.0f));

	TexCoords = texCoords;
	Normal = normal;

	fColor = color;
}