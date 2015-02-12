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
#include "Game.h"
#include "Enemy.h"
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
	

	Text font = Text("../NLuceGameEngine/fonts/font.png");

	Texture backgroundTexture("Contra_Waterfall_stage_3.png");
	backgroundTexture.filterNearest();
	const float mapWidth = 256;
	
	theGame.mapSize = vec2(backgroundTexture.getWidth(), backgroundTexture.getHeight());
	theGame.map = new Map();

	
	Shape background(&backgroundTexture, BOTTOM_LEFT);

	Texture titleTexture("Title.png");
	titleTexture.filterNearest();
	Shape titleShape(&titleTexture, CENTER);
	Sprite titleSprite;
	titleSprite.setShape(&titleShape);


	//create shader program
//	GLuint uiProgramFlat = CreateProgram("VertexPositionColorUV.glsl.glsl", "FlatFragmentShader.glsl");
	GLuint uiProgramColorTexture = CreateProgram("VertexPositionColorUV.glsl", "TexturedFragmentShader.glsl");
//	GLuint uiProgramTexture = CreateProgram("VertexPositionUV.glsl", "FragmentPositionUV.glsl");

	//find the position of the matrix variable in the shader so we can send info there later
	GLuint shaderIDMVP = glGetUniformLocation(uiProgramColorTexture, "MVP");

	float centerX = SCREEN_WIDTH / 2;
	float centerY = SCREEN_HEIGHT / 2;

	// screen is with origin at lower left (y is up)
	mat4 screen = glm::ortho(0.0f, (float)SCREEN_WIDTH, 0.0f, (float)SCREEN_HEIGHT);

	// screenCentered is with origin at center (y is up)
	mat4 screenCentered = glm::ortho(-centerX, centerX, -centerY, centerY);

	// screenCenteredx2 is centered and scaled up by 2
	mat4 screenCenteredx2 = scale(screenCentered, vec3(2, 2, 1));


	// set up blending so that the texture can have treanspeanancy...
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Bill contraDude;
	contraDude.setPosition(vec2(50, 50));
	
	Sprite backgroundSprite;
	backgroundSprite.setShape(&background);
	backgroundSprite.setPosition(vec2(0, 0));

	int highScore = 0;
	float lastTime = 0;

	float cameraHeight = 96;

	theGame.startLevel();

	float lastSpawn = 5;

	//loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		theGame.startFrame();

		// game physics
		{

			// spawn enemies
			if (theGame.time - lastSpawn > 1)
			{
				float x = rand() % int(theGame.mapSize.x);
				float y = contraDude.position.y + 150;
				Enemy * e = Enemy::Spawn(vec2(x, y), vec2());
				if (rand() & 1){
					e->mirror = true;
				}
				lastSpawn += 1;
			}


			// move the dude
			contraDude.move(window);
			Enemy::playerPosition = contraDude.position;

			// move the bullets
			Bullet::moveAll();

			// move the enemies
			Enemy::moveAll();


			{
				// check to see if any bullets hit any enemies

				// loop through all the bullets with an iterator
				auto it2 = Bullet::bulletList.begin();
				while (it2 < Bullet::bulletList.end()){
					Bullet * bullet = *it2;

					// loop through all the enemies with an iterator
					auto it = Enemy::enemyList.begin();
					while (it < Enemy::enemyList.end()){
						Enemy * enemy = *it;

						// this is where we check to see if the bullet hit the enemy
						if (bullet->collidesWith(*enemy))
						{
							bullet->dead = true;
							enemy->dead = true;
							highScore++;
						}

						if (enemy->dead)
						{
							it = Enemy::enemyList.erase(it);
							delete enemy;
						}
						else
						{
							it++;
						}
					}

					if (bullet->dead)
					{
						it2 = Bullet::bulletList.erase(it2);
						delete bullet;

					}
					else
					{
						it2++;
					}

				}


			}

		}
		//draw code goes here
		const float gameScale = SCREEN_WIDTH / mapWidth;
//		mat4 world = translate(screen, vec3(320 - contraDude.position.x, 0, 0)); // horizontal scrolling
		mat4 world = screen;


		//if (contraDude.position.y > cameraHeight)
		{
			cameraHeight = contraDude.position.y;
			if (cameraHeight < 96) cameraHeight = 96;
			//cout << cameraHeight << endl;
		}

		world = translate(world, vec3(0, centerY, 0)); // center on screen
		world = scale(world, vec3(gameScale, gameScale, 1.0)); // scale to screen
		world = translate(world, vec3(0, -cameraHeight, 0)); // vertical scrolling

		{
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//enable shaders
			glUseProgram(uiProgramColorTexture);
			//glUseProgram(uiProgramFlat);

			backgroundSprite.draw(world, shaderIDMVP);

			contraDude.draw(world, shaderIDMVP);

			Bullet::drawAll(world, shaderIDMVP);
			Enemy::drawAll(world, shaderIDMVP);

			char buffer[200];
			
			sprintf_s(buffer, "HIGH SCORE %d", highScore);
			
			font.drawString(screen, shaderIDMVP, buffer, 50, 150);
			//font.drawString(screen, shaderIDMVP, "MORE TEXT", 50, 100);
			//swap front and back buffers

			{
				// draw the title graphic
				static const float fadeIn = 1;
				static const float hold = 4;
				static const float fadeOut = 1;
				static const float totalTime = fadeIn + hold + fadeOut;
				static const float moveDistance = 250;

				if (theGame.time < totalTime)
				{
					float offset = 0;
					if (theGame.time <= fadeIn)
					{
						offset = (fadeIn - theGame.time) / fadeIn;
					}
					else if (theGame.time >= fadeIn + hold)
					{
						offset = -(theGame.time - (fadeIn + hold)) / fadeOut;
					}

					titleSprite.setRotation(offset * 3);
					titleSprite.setPosition(vec2(0, offset * moveDistance));

					titleSprite.draw(screenCenteredx2, shaderIDMVP);
				}
			}

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