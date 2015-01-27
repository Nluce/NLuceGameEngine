#include <GL/glew.h>
#include <GL/wglew.h>
#include "GLFW\glfw3.h"
#include <vector>
#include <string>
#include <fstream>
#include "Shape.h"
#include <iostream>
#include <time.h>
#include "Texture.h"
#include "Text.h"
#include "Sprite.h"

using namespace std;

// using GLM for matrix and vector classes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint CreateProgram(const char *a_vertex, const char *a_frag);

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;


int main()
{
	//Initialise GLFW
	if (!glfwInit())
	{
		return -1;
	}

	//create a windowed mode window and it's OpenGL context
	GLFWwindow* window;
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	
	//make the window's context current
	glfwMakeContextCurrent(window);

	//………Insert this into the main.cpp example given in the setting up GLFW section – 
	//once the glfw window has been created and after 'glfwMakeContextCurrent(window);'
	// start GLEW
	if (glewInit() != GLEW_OK)
	{
		// OpenGL didn't start-up! shutdown GLFW and return an error code
		glfwTerminate();
		return -1;
	}

	// load a texture to use
	int width = 200, height = 200, bpp = 4;
	Texture tex;
	tex.load("texture.png", width, height, bpp);
	Shape playerShape = Shape(&tex, CENTER);

	Text font = Text("../NLuceGameEngine/fonts/font.png");

	Texture contraSpriteSheet("ContraSprites.png");
	Texture backgroundTexture("Level.png");

	contraSpriteSheet.filterNearest();
	Shape background(&backgroundTexture,BOTTOM_LEFT);

	Shape contraRunFrame1(&contraSpriteSheet, 0, 6, 19, 36, BOTTOM_CENTER);
	Shape contraRunFrame2(&contraSpriteSheet, 37, 6, 24, 37, BOTTOM_CENTER);
	Shape contraRunFrame3(&contraSpriteSheet, 77, 6, 24, 37, BOTTOM_CENTER);
	Shape contraRunFrame4(&contraSpriteSheet, 115, 6, 24, 37, BOTTOM_CENTER);
	Shape contraRunFrame5(&contraSpriteSheet, 157, 6, 24, 37, BOTTOM_CENTER);

	Shape contraStandFrame(&contraSpriteSheet, 196, 6, 24, 37, BOTTOM_CENTER);

	Shape contraLaydownFrame(&contraSpriteSheet, 270, 6, 24, 37, BOTTOM_CENTER);

	Shape contraJumpFrame1(&contraSpriteSheet, 0, 51, 24, 24, BOTTOM_CENTER);
	Shape contraJumpFrame2(&contraSpriteSheet, 41, 51, 24, 24, BOTTOM_CENTER);
	Shape contraJumpFrame3(&contraSpriteSheet, 80, 51, 24, 24, BOTTOM_CENTER);
	Shape contraJumpFrame4(&contraSpriteSheet, 120, 51, 24, 24, BOTTOM_CENTER);


	//create shader program
//	GLuint uiProgramFlat = CreateProgram("VertexPositionColorUV.glsl.glsl", "FlatFragmentShader.glsl");
	GLuint uiProgramColorTexture = CreateProgram("VertexPositionColorUV.glsl", "TexturedFragmentShader.glsl");
//	GLuint uiProgramTexture = CreateProgram("VertexPositionUV.glsl", "FragmentPositionUV.glsl");

	//find the position of the matrix variable in the shader so we can send info there later
	GLuint shaderIDMVP = glGetUniformLocation(uiProgramColorTexture, "MVP");

	glm::mat4 ortho = glm::ortho(0.0f, (float)SCREEN_WIDTH, 0.0f, (float)SCREEN_HEIGHT);

	for (int y = 0; y < 4; y++){
		for (int x = 0; x < 4; x++){
			cout << x << ", " << y << " = " << ortho[x][y] << endl;
		}
	}

	// set up blending so that the texture can have treanspeanancy...
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	clock_t start_time = clock();

	glm::vec3 zAxis(0, 0, 1);

	float centerX = SCREEN_WIDTH / 2;
	float centerY = SCREEN_HEIGHT / 2;

	Sprite sprite1;
	sprite1.setShape(&playerShape);
	sprite1.setPosition(vec2(centerX + 50, centerY));

	Sprite sprite2;
	sprite2.setShape(&playerShape);
	sprite2.setPosition(vec2(centerX - 50, centerY));


	Sprite contraDude;
	contraDude.setShape(&contraRunFrame1);
	contraDude.setPosition(vec2(50, 50));

	Sprite contraDudeJump;
	contraDudeJump.setShape(&contraJumpFrame1);
	contraDudeJump.setPosition(vec2(100, 50));

	Sprite backgroundSprite;
	backgroundSprite.setShape(&background);
	backgroundSprite.setPosition(vec2(0, 0));

	int highScore = 0;
	//loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{

		// game physics
		{
			highScore += 10;

			float time = (float)(clock() - start_time) / CLOCKS_PER_SEC;
			sprite1.setRotation(-time / 10);
			sprite2.setRotation(time / 5 );
						
			int numberOfRunFrames = 5;
			int numberOfJumpFrames = 4;
			int animationSpeedInFramesPerSecond = 2;

			int state = glfwGetKey(window, GLFW_KEY_E);
			if (state == GLFW_PRESS)
			{
				animationSpeedInFramesPerSecond = 8;
			}
			int runFrame = int(time * animationSpeedInFramesPerSecond) % numberOfRunFrames;
			int JumpFrame = int(time * animationSpeedInFramesPerSecond) % numberOfJumpFrames;
			
			
			
			switch (runFrame)
			{
			case 0:
				contraDude.setShape(&contraRunFrame1);
				break;
			case 1:
				contraDude.setShape(&contraRunFrame2);
				break;
			case 2:
				contraDude.setShape(&contraRunFrame3);
				break;
			case 3:
				contraDude.setShape(&contraRunFrame4);
				break;
			case 4:
				contraDude.setShape(&contraRunFrame5);
				break;
			}
			switch (JumpFrame)
			{
			case 0:
				contraDudeJump.setShape(&contraJumpFrame1);
				break;
			case 1:
				contraDudeJump.setShape(&contraJumpFrame2);
				break;
			case 2:
				contraDudeJump.setShape(&contraJumpFrame3);
				break;
			case 3:
				contraDudeJump.setShape(&contraJumpFrame4);
				break;
			}
		}

		//draw code goes here
		{
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//enable shaders
			glUseProgram(uiProgramColorTexture);
			//glUseProgram(uiProgramFlat);

			backgroundSprite.draw(ortho, shaderIDMVP);

			sprite1.draw(ortho, shaderIDMVP);
			sprite2.draw(ortho, shaderIDMVP);

			contraDude.draw(ortho, shaderIDMVP);
			contraDudeJump.draw(ortho, shaderIDMVP);

			char buffer[200];

			sprintf_s(buffer, "HIGH SCORE %d", highScore);

			font.drawString(ortho, shaderIDMVP, buffer, 50, 150);

			//swap front and back buffers
			glfwSwapBuffers(window);
		}


		//poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile)
{
	std::string strShaderCode;
	//open shader file
	std::ifstream shaderStream(a_strShaderFile);
	//if that worked ok, load file line by line
	if (shaderStream.is_open())
	{
		std::string Line = "";
		while (std::getline(shaderStream, Line))
		{
			strShaderCode += "\n" + Line;
		}
		shaderStream.close();
	}

	//convert to cstring
	char const *szShaderSourcePointer = strShaderCode.c_str();

	//create shader ID
	GLuint uiShader = glCreateShader(a_eShaderType);
	//load source code
	glShaderSource(uiShader, 1, &szShaderSourcePointer, NULL);

	//compile shader
	glCompileShader(uiShader);

	//check for compilation errors and output them
	GLint iStatus;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iStatus);
	if (iStatus == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(uiShader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch (a_eShaderType)
		{
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}

	return uiShader;
}

GLuint CreateProgram(const char *a_vertex, const char *a_frag)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(CreateShader(GL_VERTEX_SHADER, a_vertex));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, a_frag));

	//create shader program ID
	GLuint uiProgram = glCreateProgram();

	//attach shaders
	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
		glAttachShader(uiProgram, *shader);

	//link program
	glLinkProgram(uiProgram);

	//check for link errors and output them
	GLint status;
	glGetProgramiv(uiProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(uiProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(uiProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glDetachShader(uiProgram, *shader);
		glDeleteShader(*shader);
	}

	return uiProgram;
}