#pragma once
#include "Sprite.h"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <stdio.h>
#include <iostream>
using namespace std;
class Bill :
	public Sprite
{
public:
	Bill()
	{
		init();
	}
	virtual ~Bill();
	vec3 platformList[7];
	

	int speed = 100;
	int numberOfRunFrames = 5;
	int numberOfJumpFrames = 4;
	int animationSpeedInFramesPerSecond = 10;
	int jump = 200;
	int drop = 10;
	int screenHeight = 480;
	double gravity = 250.0f;

	bool isRunning = false;
	bool isJumping = false;
	bool onTheGround = false;
	bool facingLeft = false;
	bool isOnPlatform = false;
	bool isDropping = false;


	vec2 preMove;
	vec2 postMove;

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

	Shape* contraJumpLeftFrame1;
	Shape* contraJumpLeftFrame2;
	Shape* contraJumpLeftFrame3;
	Shape* contraJumpLeftFrame4;

	std::vector<Shape *> shapesToDelete;

	void move(float elapsedTime, GLFWwindow* window,float time)
	{
		

		int stateSpace = glfwGetKey(window, GLFW_KEY_SPACE);
		if (stateSpace == GLFW_PRESS && onTheGround)
		{
			//setVelocity(vec2(0, speed));
			velocity.y = jump;
			isJumping = true;
		}

		int stateA = glfwGetKey(window, GLFW_KEY_A);
		if (stateA == GLFW_PRESS)
		{
			//setVelocity(vec2(- speed, 0));
			velocity.x = -speed;
			isRunning = true;
			facingLeft = true;
		}
		

		int stateS = glfwGetKey(window, GLFW_KEY_S);
		isDropping = false;
		if (stateS == GLFW_PRESS)
		{
			if (isOnPlatform)
			{
				position.y - drop;
				isJumping = true;
				isDropping = true;
			}
			
		}


		int stateD = glfwGetKey(window, GLFW_KEY_D);
		if (stateD == GLFW_PRESS)
		{
			velocity.x = speed;
			isRunning = true;
			facingLeft = false;
		}

		velocity.y -= gravity * elapsedTime;

		if (stateD == GLFW_RELEASE && stateA == GLFW_RELEASE)
		{
			velocity.x = 0;
			isRunning = false;
		}

		if (position.y < 0)
		{
			position.y = 0;
			onTheGround = true;
			isJumping = false;
			velocity.y = 0;
		}

		

		else
		{
			onTheGround = false;
		}

		preMove = position;
		postMove = preMove + velocity * elapsedTime;

		isOnPlatform = false;
		if (!isDropping)
		{

			for (int i = 0; i < 7; i++)
			{
				if (preMove.x > platformList[i].x && preMove.x < platformList[i].z)
				{
					if (preMove.y >= platformList[i].y && postMove.y < platformList[i].y)
					{
						isOnPlatform = true;
						onTheGround = true;
						isJumping = false;
						velocity.y = 0;
						position.y = platformList[i].y;
					}

				}
			}
		
		}

		if (isOnPlatform)
		{
			velocity.y = 0;
		}



		if (position.x < 4)
		{
			position.x = 4;
		}
		if (position.x > 636)
		{
			position.x = 636;
		}



		position += velocity * elapsedTime; 

		

		//cout << velocity.y << endl;

		int runFrame = int(time * animationSpeedInFramesPerSecond) % numberOfRunFrames;
		int JumpFrame = int(time * animationSpeedInFramesPerSecond) % numberOfJumpFrames;

		if (isRunning && !isJumping)
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
			if (facingLeft)
			{

				switch (JumpFrame)
				{
				case 0:
					setShape(contraJumpLeftFrame1);
					break;
				case 1:
					setShape(contraJumpLeftFrame2);
					break;
				case 2:
					setShape(contraJumpLeftFrame3);
					break;
				case 3:
					setShape(contraJumpLeftFrame4);
					break;
				}
			}
			else
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

		platformList[0] = vec3(0, screenHeight - 427, 77);
		platformList[1] = vec3(77, screenHeight - 367, 310);
		platformList[2] = vec3(302, screenHeight - 305, 389);
		platformList[3] = vec3(392, screenHeight - 367, 640);
		platformList[4] = vec3(77, screenHeight - 246, 310);
		platformList[5] = vec3(77, screenHeight - 190, 230);
		platformList[6] = vec3(230, screenHeight - 132, 640);



		contraJumpLeftFrame1 = makeMirrorShape(contraJumpFrame1);
		contraJumpLeftFrame2 = makeMirrorShape(contraJumpFrame2);
		contraJumpLeftFrame3 = makeMirrorShape(contraJumpFrame3);
		contraJumpLeftFrame4 = makeMirrorShape(contraJumpFrame4);
	
		setShape(contraRunFrame1);
	}

};

