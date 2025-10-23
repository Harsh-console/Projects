#version 330 core

layout(location = 0) in vec3 aPos; // Vertex position input
layout(location = 1) in vec3 aColor; // Vertex Color input

out vec3 color;

uniform float scale;

void main()
{
	// Transform the vertex position to clip space
	gl_Position = vec4(aPos.x + aPos.x*scale, aPos.y + aPos.y*scale, aPos.z + aPos.z*scale, 1.0);
	color = aColor;
}