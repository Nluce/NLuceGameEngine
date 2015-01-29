#pragma once
#include "Sprite.h"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW\glfw3.h>
#include <vector>
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
	int animationSpeedInFramesPerSecond = 10;

	bool isRunning = false;
	bool isJumping = false;
	bool facingLeft = false;

	Texture* contraSpriteSheet;
	Shape* contraRunFrame1;
	Shape* contraRunFrame2;
	Shape* contraRunFrame3;
	Shape* contraRunFrame4;
	Shape* contraRunFrame5;

	Shape* contraRunLeftFrame1;
	Shape* contraRunLeftFrame2;
	Shape* contraRunLeftFrame3;
	Shape* contraRunLeftFrame4;
	Shape* contraRunLeftFrame5;
	
	Shape* contraStandFrame;
	Shape* contraStandLeftFrame;

	Shape* contraJumpFrame1;
	Shape* contraJumpFrame2;
	Shape* contraJumpFrame3;
	Shape* contraJumpFrame4;

	std::vector<Shape *> shapesToDelete;

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
			facingLeft = true;
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
			facingLeft = false;
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

			if (facingLeft)
			{
				switch (runFrame)
				{
				case 0:
					setShape(contraRunLeftFrame1);
					break;
				case 1:
					setShape(contraRunLeftFrame2);
					break;
				case 2:
					setShape(contraRunLeftFrame3);
					break;
				case 3:
					setShape(contraRunLeftFrame4);
					break;
				case 4:
					setShape(contraRunLeftFrame5);
					break;

				}

			}
			else
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
			if (facingLeft)
			{
				setShape(contraStandLeftFrame);
			}
			else
			{
				setShape(contraStandFrame);
			}
		}
	}
	
	Shape * makeShape(int left, int top, int width, int height)
	{
		Shape * shape = new Shape(contraSpriteSheet, left, top, width, height, BOTTOM_CENTER, false);
		shapesToDelete.push_back(shape);
		return shape;
	}

	Shape * makeMirrorShape(Shape * origionalShape)
	{
		Shape * shape = new Shape(origionalShape, true);
		shapesToDelete.push_back(shape);
		return shape;
	}

	void init()
	{
		contraSpriteSheet = new Texture("ContraSprites.png");
		contraSpriteSheet->filterNearest();

		bool mirror = true;

		contraRunFrame1 = makeShape(0, 6, 19, 36);
		contraRunFrame2 = makeShape(37, 6, 24, 37);
		contraRunFrame3 = makeShape(77, 6, 24, 37);
		contraRunFrame4 = makeShape(115, 6, 24, 37);
		contraRunFrame5 = makeShape(157, 6, 24, 37);

		contraRunLeftFrame1 = makeMirrorShape(contraRunFrame1);
		contraRunLeftFrame2 = makeMirrorShape(contraRunFrame2);
		contraRunLeftFrame3 = makeMirrorShape(contraRunFrame3);
		contraRunLeftFrame4 = makeMirrorShape(contraRunFrame4);
		contraRunLeftFrame5 = makeMirrorShape(contraRunFrame5);

		contraStandFrame = makeShape(196, 6, 24, 37);
		contraStandLeftFrame = makeMirrorShape(contraStandFrame);

		contraJumpFrame1 = makeShape(0, 51, 24, 24);
		contraJumpFrame2 = makeShape(41, 51, 24, 24);
		contraJumpFrame3 = makeShape(80, 51, 24, 24);
		contraJumpFrame4 = makeShape(120, 51, 24, 24);
	
		setShape(contraRunFrame1);
	}

};

