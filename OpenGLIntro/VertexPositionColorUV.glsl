#version 400

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec2 UVin;

uniform mat4 MVP;

smooth out vec4 vertColour;

out vec2 UV; // output name must match input name in fragment shader

void main()
{
	UV = UVin;
	vertColour = colour;
    vec4 scaledPosition = MVP * position;
	gl_Position = scaledPosition;
}