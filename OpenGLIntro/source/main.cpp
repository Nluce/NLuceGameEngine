#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <string>
#include <fstream>
#include "Shape.h"
#include <iostream>
#include <time.h>
#include "Texture.h"
#include "Text.h"
#include "Sprite.h"
#include "Bill.h"
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

	//���Insert this into the main.cpp example given in the setting up GLFW section � 
	//once the glfw window has been created and after 'glfwMakeContextCurrent(window);'
	// start GLEW
	if (glewInit() != GLEW_OK)
	{
		// OpenGL didn't start-up! shutdown GLFW and return an error code
		glfwTerminate();
		return -1;
	}

	// load a texture to use
	

	Text font = Text("../NLuceGameEngine/fonts/font.png");

	Texture backgroundTexture("Level.png");

	
	
	
	Shape background(&backgroundTexture,BOTTOM_LEFT);



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



	Bill contraDude;
	
	contraDude.setPosition(vec2(50, 50));

	

	Sprite backgroundSprite;
	backgroundSprite.setShape(&background);
	backgroundSprite.setPosition(vec2(0, 0));

	int highScore = 0;
	float lastTime = 0;

	//loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{

		// game physics
		{
			highScore += 10;

			float time = (float)(clock() - start_time) / CLOCKS_PER_SEC;

			float elapsedTime = time - lastTime;
			lastTime = time;


			// Input
			contraDude.move(elapsedTime, window,time);
		}
		//draw code goes here
		{
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//enable shaders
			glUseProgram(uiProgramColorTexture);
			//glUseProgram(uiProgramFlat);

			backgroundSprite.draw(ortho, shaderIDMVP);

			contraDude.draw(ortho, shaderIDMVP);

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