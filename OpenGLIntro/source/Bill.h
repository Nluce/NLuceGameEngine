#pragma once
#include "Sprite.h"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW\glfw3.h>
class Bill :
	public Sprite
{
public:
	Bill()
	{
		init();
	}
	virtual ~Bill();

	int speed = 100;
	int numberOfRunFrames = 5;
	int numberOfJumpFrames = 4;
	int animationSpeedInFramesPerSecond = 2;

	bool isRunning = false;
	bool isJumping = false;
	Texture* contraSpriteSheet;
	Shape* contraRunFrame1;
	Shape* contraRunFrame2;
	Shape* contraRunFrame3;
	Shape* contraRunFrame4;
	Shape* contraRunFrame5;

	Shape* contraStandFrame;


	Shape* contraJumpFrame1;
	Shape* contraJumpFrame2;
	Shape* contraJumpFrame3;
	Shape* contraJumpFrame4;
	void move(float elapsedTime, GLFWwindow* window,float time)
	{
		
		int stateW = glfwGetKey(window, GLFW_KEY_W);
		if (stateW == GLFW_PRESS)
		{
			setVelocity(vec2(0, speed));
			isRunning = true;
		}

		int stateA = glfwGetKey(window, GLFW_KEY_A);
		if (stateA == GLFW_PRESS)
		{
			setVelocity(vec2(- speed, 0));
			isRunning = true;
		}
		

		int stateS = glfwGetKey(window, GLFW_KEY_S);
		if (stateS == GLFW_PRESS)
		{
			setVelocity(vec2( 0, - speed));
			isRunning = true;
		}


		int stateD = glfwGetKey(window, GLFW_KEY_D);
		if (stateD == GLFW_PRESS)
		{
			setVelocity(vec2(speed, 0));
			isRunning = true;
		}



		if (stateD == GLFW_RELEASE && stateA == GLFW_RELEASE && stateW == GLFW_RELEASE && stateS == GLFW_RELEASE)
		{
			setVelocity(vec2(0, 0));
			isRunning = false;
		}
		position += velocity * elapsedTime; 

		int runFrame = int(time * animationSpeedInFramesPerSecond) % numberOfRunFrames;
		int JumpFrame = int(time * animationSpeedInFramesPerSecond) % numberOfJumpFrames;

		if (isRunning)
		{
			switch (runFrame)
			{
			case 0:
				setShape(contraRunFrame1);
				break;
			case 1:
				setShape(contraRunFrame2);
				break;
			case 2:
				setShape(contraRunFrame3);
				break;
			case 3:
				setShape(contraRunFrame4);
				break;
			case 4:
				setShape(contraRunFrame5);
				break;

			}
		}
		else if (isJumping)
		{
			switch (JumpFrame)
			{
			case 0:
				setShape(contraJumpFrame1);
				break;
			case 1:
				setShape(contraJumpFrame2);
				break;
			case 2:
				setShape(contraJumpFrame3);
				break;
			case 3:
				setShape(contraJumpFrame4);
				break;
			}
		}
		else
		{
			setShape(contraStandFrame);
		}
	}
	

	void init()
	{
		contraSpriteSheet = new Texture("ContraSprites.png");
		contraSpriteSheet->filterNearest();

		contraRunFrame1 = new Shape(contraSpriteSheet, 0, 6, 19, 36, BOTTOM_CENTER);
		contraRunFrame2 = new Shape(contraSpriteSheet, 37, 6, 24, 37, BOTTOM_CENTER);
		contraRunFrame3 = new Shape(contraSpriteSheet, 77, 6, 24, 37, BOTTOM_CENTER);
		contraRunFrame4 = new Shape(contraSpriteSheet, 115, 6, 24, 37, BOTTOM_CENTER);
		contraRunFrame5 = new Shape(contraSpriteSheet, 157, 6, 24, 37, BOTTOM_CENTER);

		contraStandFrame = new Shape(contraSpriteSheet, 196, 6, 24, 37, BOTTOM_CENTER);

		contraJumpFrame1 = new Shape(contraSpriteSheet, 0, 51, 24, 24, BOTTOM_CENTER);
		contraJumpFrame2 = new Shape(contraSpriteSheet, 41, 51, 24, 24, BOTTOM_CENTER);
		contraJumpFrame3 = new Shape(contraSpriteSheet, 80, 51, 24, 24, BOTTOM_CENTER);
		contraJumpFrame4 = new Shape(contraSpriteSheet, 120, 51, 24, 24, BOTTOM_CENTER);
	
		setShape(contraRunFrame1);
	}

};

