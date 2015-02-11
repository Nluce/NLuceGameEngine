#pragma once
#include <GL/glew.h>
#include <GL/wglew.h>
#include "GLFW\glfw3.h"

// using GLM for matrix and vector classes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW\glfw3.h>
#include "Shape.h"
#include <iostream>

using namespace glm;
using namespace std;

static const vec3 zAxis(0, 0, 1);

class Sprite
{
protected:
	float rotation; // around z axis
	Shape * shape;

public:
	bool mirror;
	Sprite();
	virtual ~Sprite();

	vec2 position;
	vec2 velocity;

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
	void setVelocity(const vec2 & newVelocity)
	{
		velocity = newVelocity;
	}
	vec2 getPosition()
	{
		return position; 
	}
	vec2 getVelocity()
	{
		return velocity;
	}
	void setRotation(float newRotation)
	{
		rotation = newRotation;
	}

	void draw(const mat4 & matrixIn, int matrixUniformID)
	{
		if (shape)
		{
			mat4 out = matrixIn;

			// then we move it to where we want it centered on the screen
			out = translate(out, vec3(position.x, position.y, 0.0f));

			// first we need to rotate the model
			out = rotate(out, rotation, zAxis);

			if (mirror)
			{
				out = scale(out, vec3(-1, 1, 1));
			}

			//send our mvp matrix to the shader
			glUniformMatrix4fv(matrixUniformID, 1, GL_FALSE, &out[0][0]);

			shape->draw();
		}
		else
		{
			cerr << "No shape to draw" << endl;
		}

	}

	float getLeft() const
	{
		if (shape) {
			if (mirror) {
				return position.x - shape->right;
			}
			else {
				return position.x + shape->left;
			}
		}
		return position.x;
	}

	float getRight() const
	{
		if (shape) {
			if (mirror) {
				return position.x - shape->left;
			}
			else {
				return position.x + shape->right;
			}
		}
		return position.x;
	}

	float getTop() const
	{
		if (shape) {		
			return position.y + shape->top;
		}
		return position.y;
	}

	float getBottom() const
	{
		if (shape) {
			return position.y + shape->bottom;
		}
		return position.y;
	}

	bool collidesWith(const Sprite & otherSprite)
	{
		if (getRight() > otherSprite.getLeft()){
			if (otherSprite.getRight() > getLeft()){
				if (getBottom() < otherSprite.getTop()){
					if (otherSprite.getBottom() < getTop()){
						return true;
					}
				}
			}
		}

		return false;
	}
};

