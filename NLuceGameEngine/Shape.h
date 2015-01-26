#pragma once

#include <GL/glew.h>
#include <GL/wglew.h>
#include "GLFW\glfw3.h"
#include "glm/glm.hpp"
#include "Vertex.h"
#include "Texture.h"
using namespace glm;


enum ShapeAlignment {
	CENTER,
	BOTTOM_CENTER,
	BOTTOM_LEFT,
	TOP_LEFT,
};

class Shape
{
	Vertex* vertices;
	int numberOfVerticies;
	GLuint uiVBO;
	vec2 size;
	vec2 center;
	Texture* texture;
	
	float horzontalAlignment(ShapeAlignment a)
	{
		switch (a){
		default:
		case CENTER:
			return 0.5f;
		case BOTTOM_LEFT:
		case BOTTOM_CENTER:
			return 0.0f;
		case TOP_LEFT:
			return 1.0f;
		}
	}

	float verticalAlignment(ShapeAlignment a)
	{
		switch (a){
		default:
		case CENTER:
		case BOTTOM_CENTER:
			return 0.5f;
		case BOTTOM_LEFT:
		case TOP_LEFT:
			return 0.0f;
		}
	}

	void setVertexPositions(ShapeAlignment alignment, float width, float height)
	{
		float ha = horzontalAlignment(alignment);
		float va = verticalAlignment(alignment);

		float left = -ha * width;
		float right = left + width;
		float bottom = -va * height;
		float top = bottom + height;

		vertices[0].fPositions[0] = left;
		vertices[0].fPositions[1] = bottom;
		vertices[0].fPositions[2] = 0.0f;
		vertices[0].fPositions[3] = 1.0f;

		vertices[1].fPositions[0] = right;
		vertices[1].fPositions[1] = bottom;
		vertices[1].fPositions[2] = 0.0f;
		vertices[1].fPositions[3] = 1.0f;

		vertices[2].fPositions[0] = right;
		vertices[2].fPositions[1] = top;
		vertices[2].fPositions[2] = 0.0f;
		vertices[2].fPositions[3] = 1.0f;

		vertices[3].fPositions[0] = left;
		vertices[3].fPositions[1] = top;
		vertices[3].fPositions[2] = 0.0f;
		vertices[3].fPositions[3] = 1.0f;

	}

	float calculateU(int x)
	{
		float U = (float)x / texture->getWidth();
		return U;
	}

	float calculateV(int y)
	{
		return (float)y / texture->getHeight();
	}

	void setVertexColorsToWhite()
	{
		for (int i = 0; i < numberOfVerticies; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				vertices[i].fColours[j] = 1;
			}
		}
	}

public:


	Shape();

	void registerVertexBufferObject()
	{
		//create ID for a vertex buffer object
		glGenBuffers(1, &uiVBO);

		//check it succeeded
		if (uiVBO != 0)
		{
			//bind VBO
			glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
			//allocate space for vertices on the graphics card
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numberOfVerticies, NULL, GL_STATIC_DRAW);
			//get pointer to allocated space on the graphics card
			GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			//copy data to graphics card
			memcpy(vBuffer, vertices, sizeof(Vertex) * numberOfVerticies);
			//unmap and unbind buffer
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}

	// this constructor creates a shape that is a rectangle that is centered on the texture given.
	// useful for normal sprites
	Shape(Texture * newTexture, ShapeAlignment alignment = CENTER)
	{
		texture = newTexture;
		int h = texture->getHeight();
		int w = texture->getWidth();

		vertices = new Vertex[4];
		numberOfVerticies = 4;

		setVertexPositions(alignment, w, h);

		//set up the UVs
		vertices[0].fUVs[0] = 0; // left bottom
		vertices[0].fUVs[1] = 0;
		vertices[1].fUVs[0] = 1; // right bottom
		vertices[1].fUVs[1] = 0;
		vertices[2].fUVs[0] = 1; // right top
		vertices[2].fUVs[1] = 1;
		vertices[3].fUVs[0] = 0; // left top
		vertices[3].fUVs[1] = 1;


		for (int i = 0; i < 4; i++)
		{
			vertices[i].fColours[0] = 1.0f;
			vertices[i].fColours[1] = 1.0f;
			vertices[i].fColours[2] = 1.0f;
			vertices[i].fColours[3] = 1.0f;
		}

		registerVertexBufferObject();
	}


	// creates a rectangular shape that is using a portion of the texture.
	// This is useful for sprite sheets or fonts.
	// left, top, width and height are pixel coordinates (not UV, UV will be calculated) in the texture.
	// they indicate the portion of the texture to use for the shape
	// since these are texture pixel coordinates the origin is at the top left
	Shape(Texture * newTexture, int left, int top, int width, int height, ShapeAlignment alignment = BOTTOM_LEFT)
	{
		texture = newTexture;
		int h = texture->getHeight();
		int w = texture->getWidth();

		vertices = new Vertex[4];
		numberOfVerticies = 4;

		setVertexPositions(alignment, width, height);

		//set up the UVs

		vertices[0].fUVs[0] = calculateU(left);
		vertices[0].fUVs[1] = calculateV(top + height);

		vertices[1].fUVs[0] = calculateU(left + width);
		vertices[1].fUVs[1] = calculateV(top + height);

		vertices[2].fUVs[0] = calculateU(left + width);
		vertices[2].fUVs[1] = calculateV(top);

		vertices[3].fUVs[0] = calculateU(left);
		vertices[3].fUVs[1] = calculateV(top);

		setVertexColorsToWhite();
		registerVertexBufferObject();
	}

	~Shape();
	void setTexture(Texture * newTexture)
	{
		texture = newTexture;
	}

	void setVerts(Vertex* newVerts, int numberOfVertices)
	{
		vertices = new Vertex[numberOfVertices];
		memcpy(vertices, newVerts, sizeof (Vertex) * numberOfVertices);

		this->numberOfVerticies = numberOfVertices;
		registerVertexBufferObject();
	}

	void draw()
	{
		if (uiVBO != 0)
		{
			if (texture)
			{
				texture->bind();
			}
			glBindBuffer(GL_ARRAY_BUFFER, uiVBO);

			//enable the vertex array states
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			/*Since the data is in the same array, we need to specify the gap between
			vertices (A whole Vertex structure instance) and the offset of the data
			from the beginning of the structure instance. The positions are at the
			start, so their offset is 0. But the colours are after the positions, so
			they are offset by the size of the position data */
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float) * 4));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float) * 8));

			//draw to the screen
			glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVerticies);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
};

