#pragma once
#include <GL/glew.h>
#include <GL/wglew.h>
#include "GLFW\glfw3.h"

// using GLM for matrix and vector classes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>#include <glm/gtc/type_ptr.hpp>
#include "Shape.h"

using namespace glm;

static const glm::vec3 zAxis(0, 0, 1);

class Sprite
{
	vec2 position;
	float rotation; // around z axis
	Shape * shape;
	

public:
	Sprite();
	~Sprite();

	void drawSprite();
	void moveSprite();

	void setShape(Shape * newShape)
	{
		shape = newShape;
	}

	void setPosition(const vec2 & newPosition)
	{
		position = newPosition;
	}

	void setRotation(float newRotation)
	{
		rotation = newRotation;
	}

	void draw(const mat4 & projection, int matrixUniformID)
	{
		{
			// first we need to rotate the model
			glm::mat4 rotationMatrix = glm::rotate(glm::mat4(), rotation, zAxis);

			// then we move it to where we want it centered on the screen
			glm::mat4 translationMatrix = glm::translate(glm::mat4(), vec3(position.x, position.y, 0.0f));

			// then we apply the orthographic projection to put it into opengl coordinates
			glm::mat4 mvp = projection * translationMatrix * rotationMatrix;

			//send our mvp matrix to the shader
			glUniformMatrix4fv(matrixUniformID, 1, GL_FALSE, &mvp[0][0]);
		}

		shape->draw();
	}


};

