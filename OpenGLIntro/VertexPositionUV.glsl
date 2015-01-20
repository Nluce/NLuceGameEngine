#version 400

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 UVin;

uniform mat4 MVP;

out vec2 UV; // output name must match input name in fragment shader

void main()
{
	UV = UVin;
	gl_Position = MVP * position;
}