#include "Shape.h"


Shape::Shape()
{
	vertices = 0;
}


Shape::~Shape()
{
	if (vertices != nullptr)
	{
		delete[] vertices;
	}
}


extern ShapeAlignment CENTER_LEFT(0.0f, 0.5f);
extern ShapeAlignment CENTER(0.5f, 0.5f);
extern ShapeAlignment CENTER_RIGHT(1.0f, 0.5f);

extern ShapeAlignment BOTTOM_LEFT(0.0f, 0.0f);
extern ShapeAlignment BOTTOM_CENTER(0.5f, 0.0f);
extern ShapeAlignment BOTTOM_RIGHT(1.0f, 0.0f);

extern ShapeAlignment TOP_LEFT(0.0f, 1.0f);
extern ShapeAlignment TOP_CENTER(0.5f, 1.0f);
extern ShapeAlignment TOP_RIGHT(1.0f, 1.0f);
