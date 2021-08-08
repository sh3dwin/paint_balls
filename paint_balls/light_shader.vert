#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec3 Color;
out vec2 TexCoord;

uniform vec3 aColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	TexCoord = aTexCoords;
	Color = aColor;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}