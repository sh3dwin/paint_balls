#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 Color;

uniform vec3 aColor;


void main()
{
	Color = aColor;
	gl_Position = vec4(aPos, 1.0f);
}