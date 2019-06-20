#version 330 core


in vec3 ourColor;
in vec2 TexCoord;
//in vec3 test_position;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
	//color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	//color = vertexColor;
	//color = vec4(test_position, 1.0f);
	//color = vec4(ourColor, 1.0f);
	//color = texture(ourTexture1, TexCoord) * vec4(ourColor, 1.0f);
	color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.3);

}