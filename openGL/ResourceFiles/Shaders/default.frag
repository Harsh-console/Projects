#version 330 core

out vec4 FragColor; // Output color of the fragment
in vec3 color;

void main()
{
	FragColor = vec4(color, 1.0); // color
}