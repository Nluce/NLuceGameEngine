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
	vec3 platformList[66];


	int speed = 100;
	int numberOfRunFrames = 5;
	int numberOfJumpFrames = 4;
	int numberOfRunDiagonalFrames = 3;
	int numberOfDeadFrames = 5;
	int animationSpeedInFramesPerSecond = 10;
	int jump = 200;
	int drop = 10;
	int mapHeight = 2159;
	double gravity = 250.0f;

	bool isRunning = false;
	bool isJumping = false;
	bool onTheGround = false;
	bool facingLeft = false;
	bool isOnPlatform = false;
	bool isDropping = false;
	bool lookingUp = false;
	bool lookingDown = false;
	bool dead = false;
	bool shapeHasBeenSet = false;
	bool lookingDiagonal = false;
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

	Shape* contraShootRightStand_ShootRightRunFrame1;
	Shape* contraShootRightRunFrame2;
	Shape* contraShootRightRunFrame3;

	Shape* contraShootUpRightRunFrame1;
	Shape* contraShootUpRightRunFrame2;
	Shape* contraShootUpRightRunFrame3;

	Shape* contraShootDownRightRunFrame1;
	Shape* contraShootDownRightRunFrame2;
	Shape* contraShootDownRightRunFrame3;

	Shape* contraShootStraightUpRightFrame;
	Shape* contraLayDownRightFrame;

	Shape* contraShootStraightUpLeftFrame;
	Shape* contraLayDownLeftFrame;

	Shape* contraShootLeftStand_ShootLeftRunFrame1;
	Shape* contraShootLeftRunFrame2;
	Shape* contraShootLeftRunFrame3;

	Shape* contraShootUpLeftRunFrame1;
	Shape* contraShootUpLeftRunFrame2;
	Shape* contraShootUpLeftRunFrame3;

	Shape* contraShootDownLeftRunFrame1;
	Shape* contraShootDownLeftRunFrame2;
	Shape* contraShootDownLeftRunFrame3;

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

	Shape* contraRightDeathFlipFrame1;
	Shape* contraRightDeathFlipFrame2;
	Shape* contraRightDeathFlipFrame3;
	Shape* contraRightDeathFlipFrame4;

	Shape* contraLeftDeathFlipFrame1;
	Shape* contraLeftDeathFlipFrame2;
	Shape* contraLeftDeathFlipFrame3;
	Shape* contraLeftDeathFlipFrame4;

	Shape* contraRightDead;
	Shape* contraLeftDead;

	std::vector<Shape *> shapesToDelete;



	void move(float elapsedTime, GLFWwindow* window, float time)
	{
		bool stateSpace = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
		bool stateLeft = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
		bool stateDown = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
		bool stateRight = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
		bool stateUp = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
		bool stateShoot = glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS;


		if (stateRight == stateLeft)
		{
			// if both on or both off
			velocity.x = 0;
			isRunning = false;
		}
		else
		{
			if (stateLeft)
			{
				velocity.x = -speed;
				isRunning = true;
				facingLeft = true;
			}

			if (stateRight)
			{
				velocity.x = speed;
				isRunning = true;
				facingLeft = false;
			}
		}


		if (stateSpace && onTheGround && !stateDown)
		{
			velocity.y = jump;
			isJumping = true;
		}

		isDropping = false;
		if (stateDown && stateSpace)
		{
			if (isOnPlatform)
			{
				position.y - drop;
				isJumping = true;
				isDropping = true;
			}
		}

		if (stateUp && onTheGround)
		{
			lookingUp = true;
		}
		else
		{
			lookingUp = false;
		}

		if (stateDown && onTheGround)
		{
			lookingDown = true;
		}
		else
		{
			lookingDown = false;
		}

		velocity.y -= gravity * elapsedTime;

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

			for (int i = 0; i < 67; i++)
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
		if (position.x > 252)
		{
			position.x = 252;
		}

		position += velocity * elapsedTime;

		//cout << velocity.y << endl;

		int runFrame = int(time * animationSpeedInFramesPerSecond) % numberOfRunFrames;
		int runDiagionalFrame = int(time * animationSpeedInFramesPerSecond) % numberOfRunDiagonalFrames;
		int JumpFrame = int(time * animationSpeedInFramesPerSecond) % numberOfJumpFrames;

		if (isRunning && lookingUp)
		{
			lookingDiagonal = true;
		}
		else if (isRunning && lookingDown)
		{
			lookingDiagonal = true;
		}
		
	

		if (isRunning && !isJumping)
		{

			if (facingLeft && lookingUp)
			{
				switch (runDiagionalFrame)
				{
				case 0:
					setShape(contraShootUpLeftRunFrame1);
					break;
				case 1:
					setShape(contraShootUpLeftRunFrame2);
					break;
				case 2:
					setShape(contraShootUpLeftRunFrame3);

					break;
				}

			}
			else if (facingLeft && lookingDown)
			{
				switch (runDiagionalFrame)
				{
				case 0:
					setShape(contraShootDownLeftRunFrame1);
					break;
				case 1:
					setShape(contraShootDownLeftRunFrame2);
					break;
				case 2:
					setShape(contraShootDownLeftRunFrame3);
					break;
				}

			}
			else if (facingLeft && !lookingDiagonal)
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

			else if (!facingLeft && lookingUp)
			{
				switch (runDiagionalFrame)
				{
				case 0:
					setShape(contraShootUpRightRunFrame1);
					break;
				case 1:
					setShape(contraShootUpRightRunFrame2);
					break;
				case 2:
					setShape(contraShootUpRightRunFrame3);
					break;
				}

			}
			else if (!facingLeft && lookingDown)
			{
				switch (runDiagionalFrame)
				{
				case 0:
					setShape(contraShootDownRightRunFrame1);
					break;
				case 1:
					setShape(contraShootDownRightRunFrame2);
					break;
				case 2:
					setShape(contraShootDownRightRunFrame3);
					break;
				}
			}
			else if (!facingLeft && !lookingDiagonal)
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
		else if (facingLeft  && lookingUp)
		{
			setShape(contraShootStraightUpLeftFrame);
		}
		else if (!facingLeft && lookingUp)
		{
			setShape(contraShootStraightUpRightFrame);
		}
		else if (facingLeft && lookingDown)
		{
			setShape(contraLayDownLeftFrame);
		}

		else if (!facingLeft && lookingDown)
		{
			setShape(contraLayDownRightFrame);
		}
		else if (facingLeft && !lookingDiagonal)
		{
				setShape(contraStandLeftFrame);
		}
		else
		{
			if (!lookingDiagonal)
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

		contraShootRightStand_ShootRightRunFrame1 = makeShape(235, 6, 24, 37);
		contraShootRightRunFrame2 = makeShape(235, 86, 24, 37);
		contraShootRightRunFrame3 = makeShape(272, 86, 24, 37);

		contraShootLeftStand_ShootLeftRunFrame1 = makeMirrorShape(contraShootRightStand_ShootRightRunFrame1);
		contraShootLeftRunFrame2 = makeMirrorShape(contraShootRightRunFrame2);
		contraShootLeftRunFrame3 = makeMirrorShape(contraShootRightRunFrame3);

		contraShootUpRightRunFrame1 = makeShape(0, 128, 19, 36);
		contraShootUpRightRunFrame2 = makeShape(31, 128, 24, 37);
		contraShootUpRightRunFrame3 = makeShape(67, 128, 24, 37);

		contraShootUpLeftRunFrame1 = makeMirrorShape(contraShootUpRightRunFrame1);
		contraShootUpLeftRunFrame2 = makeMirrorShape(contraShootUpRightRunFrame2);
		contraShootUpLeftRunFrame3 = makeMirrorShape(contraShootUpRightRunFrame3);

		contraShootStraightUpRightFrame = makeShape(319, 0, 24, 45);
		contraShootStraightUpLeftFrame = makeMirrorShape(contraShootStraightUpRightFrame);

		contraLayDownRightFrame = makeShape(271, 13, 37, 18);
		contraLayDownLeftFrame = makeMirrorShape(contraLayDownRightFrame);

		contraShootDownRightRunFrame1 = makeShape(305, 86, 24, 37);
		contraShootDownRightRunFrame2 = makeShape(335, 86, 24, 37);
		contraShootDownRightRunFrame3 = makeShape(362, 85, 24, 37);

		contraShootDownLeftRunFrame1 = makeMirrorShape(contraShootDownRightRunFrame1);
		contraShootDownLeftRunFrame2 = makeMirrorShape(contraShootDownRightRunFrame2);
		contraShootDownLeftRunFrame3 = makeMirrorShape(contraShootDownRightRunFrame3);

		contraStandFrame = makeShape(196, 6, 24, 37);
		contraStandLeftFrame = makeMirrorShape(contraStandFrame);

		contraJumpFrame1 = makeShape(0, 51, 24, 24);
		contraJumpFrame2 = makeShape(41, 51, 24, 24);
		contraJumpFrame3 = makeShape(80, 51, 24, 24);
		contraJumpFrame4 = makeShape(120, 51, 24, 24);

		contraRightDeathFlipFrame1 = makeShape(155, 53, 28, 19);
		contraRightDeathFlipFrame2 = makeShape(198, 50, 23, 25);
		contraRightDeathFlipFrame3 = makeShape(155, 53, 28, 19);
		contraRightDeathFlipFrame4 = makeShape(276, 53, 28, 21);

		contraLeftDeathFlipFrame1 = makeMirrorShape(contraRightDeathFlipFrame1);
		contraLeftDeathFlipFrame2 = makeMirrorShape(contraRightDeathFlipFrame2);
		contraLeftDeathFlipFrame3 = makeMirrorShape(contraRightDeathFlipFrame3);
		contraLeftDeathFlipFrame4 = makeMirrorShape(contraRightDeathFlipFrame4);

		contraRightDead = makeShape(311, 56, 41, 14);
		contraLeftDead = makeMirrorShape(contraRightDead);

		



		contraJumpLeftFrame1 = makeMirrorShape(contraJumpFrame1);
		contraJumpLeftFrame2 = makeMirrorShape(contraJumpFrame2);
		contraJumpLeftFrame3 = makeMirrorShape(contraJumpFrame3);
		contraJumpLeftFrame4 = makeMirrorShape(contraJumpFrame4);


		platformList[0] = vec3(0, mapHeight - 2125, 256);
		platformList[1] = vec3(160, mapHeight - 2092, 256);
		platformList[2] = vec3(128, mapHeight - 2059, 222);
		platformList[3] = vec3(0, mapHeight - 1996, 127);
		platformList[4] = vec3(160, mapHeight - 1996, 256);
		platformList[5] = vec3(32, mapHeight - 1965, 95);
		platformList[6] = vec3(128, mapHeight - 1949, 256);
		platformList[7] = vec3(96, mapHeight - 2028, 222);

		platformList[8] = vec3(0, mapHeight - 1933, 64);

		platformList[9] = vec3(192, mapHeight - 1917, 256);

		platformList[10] = vec3(64, mapHeight - 1901, 159);

		platformList[11] = vec3(0, mapHeight - 1870, 127);

		platformList[12] = vec3(32, mapHeight - 1837, 191);

		platformList[13] = vec3(0, mapHeight - 1805, 64);

		platformList[14] = vec3(192, mapHeight - 1805, 256);

		platformList[15] = vec3(32, mapHeight - 1758, 64);

		platformList[16] = vec3(128, mapHeight - 1758, 256);

		platformList[17] = vec3(32, mapHeight - 1725, 96);

		platformList[18] = vec3(0, mapHeight - 1694, 128);

		platformList[19] = vec3(160, mapHeight - 1678, 256);

		platformList[20] = vec3(0, mapHeight - 1645, 256);

		platformList[21] = vec3(0, mapHeight - 1597, 64);

		platformList[22] = vec3(0, mapHeight - 1548, 128);

		platformList[23] = vec3(32, mapHeight - 1485, 96);

		platformList[24] = vec3(64, mapHeight - 1518, 256);

		platformList[25] = vec3(128, mapHeight - 1453, 256);

		platformList[26] = vec3(32, mapHeight - 1420, 128);

		platformList[27] = vec3(0, mapHeight - 1390, 64);

		platformList[28] = vec3(0, mapHeight - 1341, 256);
		//missed this first time
		platformList[63] = vec3(192, mapHeight - 1310, 256);

		platformList[29] = vec3(160, mapHeight - 1278, 256);
		// this too
		platformList[64] = vec3(0, mapHeight - 1264, 64);

		platformList[30] = vec3(128, mapHeight - 1245, 223);

		platformList[31] = vec3(32, mapHeight - 1230, 96);

		platformList[32] = vec3(0, mapHeight - 1197, 64);

		platformList[33] = vec3(192, mapHeight - 1182, 256);

		platformList[34] = vec3(32, mapHeight - 1132, 128);

		platformList[35] = vec3(160, mapHeight - 1132, 256);

		platformList[36] = vec3(0, mapHeight - 1102, 96);

		platformList[37] = vec3(160, mapHeight - 1036, 192);

		platformList[38] = vec3(128, mapHeight - 989, 192);

		platformList[39] = vec3(160, mapHeight - 958, 223);

		platformList[40] = vec3(0, mapHeight - 926, 32);

		platformList[41] = vec3(64, mapHeight - 926, 160);

		platformList[42] = vec3(128, mapHeight - 894, 192);

		platformList[43] = vec3(64, mapHeight - 846, 223);

		platformList[44] = vec3(32, mapHeight - 814, 128);

		platformList[45] = vec3(64, mapHeight - 767, 160);

		platformList[46] = vec3(192, mapHeight - 767, 256);

		platformList[47] = vec3(192, mapHeight - 733, 223);

		platformList[48] = vec3(160, mapHeight - 702, 256);

		platformList[49] = vec3(32, mapHeight - 687, 128);

		platformList[50] = vec3(0, mapHeight - 638, 96);

		platformList[51] = vec3(192, mapHeight - 558, 256);

		platformList[52] = vec3(161, mapHeight - 526, 256);

		platformList[53] = vec3(0, mapHeight - 494, 223);

		platformList[54] = vec3(128, mapHeight - 462, 256);

		platformList[55] = vec3(0, mapHeight - 446, 96);

		platformList[56] = vec3(96, mapHeight - 414, 190);

		platformList[57] = vec3(0, mapHeight - 382, 128);

		platformList[58] = vec3(160, mapHeight - 366, 256);

		platformList[59] = vec3(32, mapHeight - 334, 96);

		platformList[60] = vec3(128, mapHeight - 300, 256);

		platformList[61] = vec3(0, mapHeight - 255, 256);

		platformList[62] = vec3(0, mapHeight - 207, 256);


		setShape(contraRunFrame1);
	}

};

