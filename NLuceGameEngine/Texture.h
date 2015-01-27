#pragma once
#include <GL/glew.h>
#include <GL/wglew.h>
#include "GLFW\glfw3.h"
#include "glm/glm.hpp"

#include "soil/SOIL.h"
#include <iostream>

class Texture
{
	int id;
	int height;
	int width;
public:
	Texture() : id(0) {}

	Texture(const char * fileName)
	{
		load(fileName);
	}

	~Texture(){}
	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}
	void load(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP)
	{
		//check file exists
		if (a_pFilename != nullptr)
		{
			//read in image data from file
			unsigned char* pImageData = SOIL_load_image(a_pFilename, &a_iWidth, &a_iHeight, &a_iBPP, SOIL_LOAD_AUTO);

			//check for successful read
			if (pImageData)
			{
				//create opengl texture handle
				id = SOIL_create_OGL_texture(pImageData, a_iWidth, a_iHeight, a_iBPP,
					SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
				//clear what was read in from file now that it is stored in the handle
				SOIL_free_image_data(pImageData);
			}

			//check for errors
			if (id == 0)
			{
				std::cerr << "SOIL loading error: " << SOIL_last_result() << std::endl;
			}
		}

		int miplevel = 0;
		bind();
		glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &height);
	}

	void load(const char* a_pFilename)
	{
		//check file exists
		if (a_pFilename != nullptr)
		{

			id = SOIL_load_OGL_texture(a_pFilename, SOIL_LOAD_RGBA, 0, SOIL_FLAG_INVERT_Y);

			//check for errors
			if (id == 0)
			{
				std::cerr << "SOIL loading error: " << SOIL_last_result() << std::endl;
			}
		}

		int miplevel = 0;
		bind();
		glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &height);
	}


	void filterNearest()
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,			GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,			GL_NEAREST);
	}


	// Binds this texture to the OpenGL 2d texture unit.
	void bind()
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}


};

