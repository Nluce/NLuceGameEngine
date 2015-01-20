#pragma once
#include <GL/glew.h>
#include <GL/wglew.h>
#include "GLFW\glfw3.h"
#include "glm/glm.hpp"
using namespace glm;
class Sprite
{
	vec2 position;
	

public:
	Sprite();
	~Sprite();

	void drawSprite();
	void moveSprite();
};

