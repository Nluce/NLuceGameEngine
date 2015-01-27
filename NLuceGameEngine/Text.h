#pragma once
#include <GL/glew.h>
#include <GL/wglew.h>
#include "GLFW\glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shape.h"
#include "Texture.h"

using namespace glm;
class Text
{
	// the texture used to draw this font
	Texture * texture;

	// the list of shapes used to draw the letters.
	Shape**charList;

	// the width of each char
	int charWidth;
	// the height of each char
	int charHeight;
	// the number of chars per row in the texture
	int charsPerRow;
	// the first char in the texture (upper left corner)
	char firstChar;

	// the scale of the font
	float scale;

public:
	Text(const char * textureFileName)
	{
		texture = new Texture();
		texture->load(textureFileName);
		texture->filterNearest();
		charHeight = 8;
		charWidth = 8;
		charsPerRow = 16;
		firstChar = ' ';
		scale = 3;
		charList = new Shape*[96];
		for (int i = 0; i < 96; i++)
		{
			charList[i] = 0;
		}
	}

private:
	int calculateLeft(char c)
	{
		int column = (c - firstChar) % charsPerRow;
		int left = column * charWidth;
		return left;
	}


	int calculateTop(char c)
	{
		int row = (c - firstChar) / charsPerRow;
		int top = row * charHeight;
		return top;
	}

	Shape* makeShape(char c)
	{
		int left = calculateLeft(c);
		int top = calculateTop(c);

		Shape * shape = new Shape(texture, left, top, charWidth, charHeight, BOTTOM_LEFT);
		return shape;
	}
public:
	void drawString(const mat4 & matrixIn, int matrixUniformID, const char * s, float x, float y)
	{
		int i = 0;
		char c = s[i];
		while (c != 0)
		{
			drawChar(matrixIn, matrixUniformID, c, x, y);
			x += charWidth;
			i++;
			c = s[i];
		}
	}

	void drawChar(const mat4 & matrixIn, int matrixUniformID, char c, float x, float y)
	{
		if (c < firstChar)
		{
			return;
		}
		if (c > 0x7f)
		{
			return;
		}

		// look to see if the shape is in the list
		Shape*shape = charList[c - firstChar];

		if (shape == 0)
		{
			// no shape for this char...  make the shape
			shape = makeShape(c);
			// and add it to the list
			charList[c - firstChar] = shape;
		}

		float rotation = 0;
		static const glm::vec3 zAxis(0, 0, 1);

		{
			// first we need to rotate the model
			glm::mat4 scaleMatrix = glm::scale(glm::mat4(), vec3(scale, scale, 1.0f));

			// then we move it to where we want it centered on the screen
			glm::mat4 translationMatrix = glm::translate(glm::mat4(), vec3(x, y, 0.0f));

			// then we apply the orthographic matrixIn to put it into opengl coordinates
			glm::mat4 mvp = matrixIn *  scaleMatrix * translationMatrix;

			//send our mvp matrix to the shader
			glUniformMatrix4fv(matrixUniformID, 1, GL_FALSE, &mvp[0][0]);
		}

		shape->draw();
	}

	~Text()
	{
		// delete all the shapes in the list

		for (int i = 0; i < 96; i++)
		{
			Shape * shape = charList[i];
			if (shape != 0){
				delete shape;
			}
		}

		// delete the list itself
		delete[]charList;

		// delete the texture
		delete texture;
	}
};

