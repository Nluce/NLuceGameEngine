#version 400

smooth in vec4 vertColour;

in vec2 UV; // input name must match output name in vertex shader

out vec4 outputColour;

uniform sampler2D myTextureSampler;

void main()
{
	outputColour = texture(myTextureSampler, UV) * vertColour;
	//outputColour = texture(myTextureSampler, UV);
	//outputColour = vertColour;

	// this code might make thing run faster
	if(false){
		if(outputColour.a < 0.01){
			discard;
		}
	}
}