#pragma once
#include <GL/glew.h>
#include <GL/wglew.h>
#include "GLFW\glfw3.h"
#include "glm/glm.hpp"

#include "Shape.h"

using namespace glm;
class Background :
	public Shape

{
public:
	Background();
	~Background();
	void bgScroll(); 
};

