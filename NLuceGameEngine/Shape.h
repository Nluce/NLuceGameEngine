#pragma once

#include <GL/glew.h>
#include <GL/wglew.h>
#include "GLFW\glfw3.h"
#include "glm/glm.hpp"
#include "Vertex.h"
using namespace glm;

class Shape
{
	Vertex* vertices;
	int numberOfNerticies;
	GLuint uiVBO;
	vec2 size;
	vec2 center;

	// add a Texture pointer to Shape

public:
	Shape();
	~Shape();
	

	void setVerts(Vertex* newVerts, int numberOfVertices)
	{
		vertices = newVerts;
		this->numberOfNerticies = numberOfVertices;

		//create ID for a vertex buffer object
		glGenBuffers(1, &uiVBO);

		//check it succeeded
		if (uiVBO != 0)
		{
			//bind VBO
			glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
			//allocate space for vertices on the graphics card
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numberOfVertices, NULL, GL_STATIC_DRAW);
			//get pointer to allocated space on the graphics card
			GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			//copy data to graphics card
			memcpy(vBuffer, vertices, sizeof(Vertex) * numberOfVertices);
			//unmap and unbind buffer
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}

	void draw()
	{
		if (uiVBO != 0)
		{
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
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float)* 8));

			//draw to the screen
			glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfNerticies);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
};

