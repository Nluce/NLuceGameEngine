#pragma once
#include <GL/glew.h>
#include <GL/wglew.h>
#include "GLFW\glfw3.h"
#include "glm/glm.hpp"

#include "Texture.h"

using namespace glm;
class Text
{
	Texture * texture;
public:
	Text(const char * textureFileName)
	{
		texture = new Texture();
		texture->load(textureFileName);
	}

	~Text(){
		delete texture;
	}
};

