#pragma once
#include <GL/glew.h>
#include <GL/wglew.h>
#include "GLFW\glfw3.h"
class SpriteList
{
	int spriteCount = 0;
public:
	SpriteList();
	~SpriteList();
	void addSprite();
};

