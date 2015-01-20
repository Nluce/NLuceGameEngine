#version 400

in vec2 UV; // input name must match output name in vertex shader

out vec4 outputColour;

uniform sampler2D myTextureSampler;

void main()
{
	outputColour = texture(myTextureSampler, UV);

	if(outputColour.a < 0.5){
		discard;
	}
}