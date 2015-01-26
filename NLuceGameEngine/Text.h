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
		int column = c % charsPerRow;
		int left = column * charWidth;
		return left;
	}

	int calculateRight(char c)
	{
		return calculateLeft(c) + charWidth;
	}

	float calculateU(int x)
	{
		float U = (float)x / texture->getWidth();
		return U;
	}

	int calculateTop(char c)
	{
		return (c - firstChar) / charsPerRow * charHeight;
	}

	int calculateBottom(char c)
	{
		return calculateTop(c) + charHeight;
	}

	float calculateV(int y)
	{
		return (float)y / texture->getHeight();
	}

	Shape* makeShape(char c)
	{
		Vertex v[4];
		v[0].fPositions[0] = 0;
		v[0].fPositions[1] = 0;
		v[0].fPositions[2] = 0;
		v[0].fPositions[3] = 1;

		v[1].fPositions[0] = charWidth;
		v[1].fPositions[1] = 0;
		v[1].fPositions[2] = 0;
		v[1].fPositions[3] = 1;

		v[2].fPositions[0] = charWidth;
		v[2].fPositions[1] = charHeight;
		v[2].fPositions[2] = 0;
		v[2].fPositions[3] = 1;

		v[3].fPositions[0] = 0;
		v[3].fPositions[1] = charHeight;
		v[3].fPositions[2] = 0;
		v[3].fPositions[3] = 1;
		
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				v[i].fColours[j] = 1;
			}
		}

		v[0].fUVs[0] = calculateU(calculateLeft(c));
		v[0].fUVs[1] = calculateV(calculateBottom(c));

		v[1].fUVs[0] = calculateU(calculateRight(c));
		v[1].fUVs[1] = calculateV(calculateBottom(c));

		v[2].fUVs[0] = calculateU(calculateRight(c));
		v[2].fUVs[1] = calculateV(calculateTop(c));

		v[3].fUVs[0] = calculateU(calculateLeft(c));
		v[3].fUVs[1] = calculateV(calculateTop(c));

		Shape * shape = new Shape();
		shape->setVerts(v, 4);
		shape->setTexture(texture);
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

		Shape*shape = charList[c - firstChar];

		if (shape == 0)
		{
			shape = makeShape(c);
			charList[c - firstChar] = shape;
		}

		float rotation = 0;
		static const glm::vec3 zAxis(0, 0, 1);

		{
			// first we need to rotate the model
			glm::mat4 rotationMatrix = glm::scale(glm::mat4(), vec3(scale, scale, 1.0f));

			// then we move it to where we want it centered on the screen
			glm::mat4 translationMatrix = glm::translate(glm::mat4(), vec3(x, y, 0.0f));

			// then we apply the orthographic matrixIn to put it into opengl coordinates
			glm::mat4 mvp = matrixIn *  rotationMatrix * translationMatrix;

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

