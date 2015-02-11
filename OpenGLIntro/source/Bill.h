#pragma once
#include "Sprite.h"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "Animation.h"
#include "Bullet.h"

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



	int speed = 100;
	int jumpSpeed = 200;
	int drop = 10;
	float reloadTime;
	double gravity = 250.0f;

	int bulletSpeed = 250;
	int fireRate = 20; // fireRate is in shots per second

	bool isJumping = false;
	bool onTheGround = false;
	bool isOnPlatform = false;
	bool facingLeft = false;
	bool gunLoaded = true;


	bool isDead = false;

	vec2 preMove;
	vec2 postMove;

	Texture* contraSpriteSheet;

	Animation run;
	Animation runShoot;
	Animation runShootUp;
	Animation runShootDown;
	Animation shootStraightUp;
	Animation layDown;
	Animation stand;
	Animation jumpAnimation;
	Animation deathFlip;
	Animation deadAnimation;

	std::vector<Shape *> shapesToDelete;

	enum Orientation {
		STANDING,
		STANDING_SHOOTING_UP,
		PRONE,
		RUNNING_SHOOTING_FORWARD,
		RUNNING_SHOOTING_UP,
		RUNNING_SHOOTING_DOWN,
		JUMPING,
		JUMPING_SHOOTING_UP,
		JUMPING_SHOOTING_UP_FORWARD,
		JUMPING_SHOOTING_FORWARD,
		JUMPING_SHOOTING_DOWN_FORWARD,
		JUMPING_SHOOTING_DOWN
	};

	void move(GLFWwindow* window)
	{
		bool jumpButton = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
		bool leftButton = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
		bool downButton = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
		bool rightButton = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
		bool upButton = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
		bool fireButton = glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS;


		bool isDropping = false;
		bool isRunning = false;
		
		if (reloadTime > 0)
		{
			reloadTime -= theGame.elapsedTime;
		}
		else
		{
			gunLoaded = true;
		}

		if (rightButton == leftButton)
		{
			// if both on or both off
			velocity.x = 0;
		}
		else
		{
			if (leftButton)
			{
				velocity.x = -speed;
				isRunning = true;
				facingLeft = true;
			}

			if (rightButton)
			{
				velocity.x = speed;
				isRunning = true;
				facingLeft = false;
			}
		}

		if (jumpButton)
		{
			if (downButton)
			{
				if (isOnPlatform)
				{
					isJumping = true;
					isDropping = true;
				}
			}
			else
			{
				if (onTheGround)
				{
					velocity.y = jumpSpeed;
					isJumping = true;
				}
			}
		}

		velocity.y -= gravity * theGame.elapsedTime;

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
		postMove = preMove + velocity * theGame.elapsedTime;

		isOnPlatform = false;


		if (!isDropping)
		{
			for (vec3 platform : theGame.map->platformList)
			{
				if (preMove.x > platform.x && preMove.x < platform.z)
				{
					if (preMove.y >= platform.y && postMove.y < platform.y)
					{
						isOnPlatform = true;
						onTheGround = true;
						isJumping = false;
						velocity.y = 0;
						position.y = platform.y;
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

		position += velocity * theGame.elapsedTime;

		//cout << velocity.y << endl;
		
		mirror = facingLeft;

		Animation * animation;
		Orientation orientation;


		if (isJumping)
		{
			animation = &jumpAnimation;
			if (upButton && !isRunning)
			{
				orientation = JUMPING_SHOOTING_UP;
			}
			else if (upButton &&isRunning)
			{
				orientation = JUMPING_SHOOTING_UP_FORWARD;
			}
			else if (downButton && isRunning)
			{
				orientation = JUMPING_SHOOTING_DOWN_FORWARD;
			}
			else if (downButton && !isRunning)
			{
				orientation = JUMPING_SHOOTING_DOWN;
			}
			else
			{
				orientation = JUMPING_SHOOTING_FORWARD;
			}
		}
		else if (isRunning)
		{
			if (upButton)
			{
				orientation = RUNNING_SHOOTING_UP;

				animation = &runShootUp;
			}
			else if (downButton)
			{
				orientation = RUNNING_SHOOTING_DOWN;
				animation = &runShootDown;
			}
			else
			{
				orientation = RUNNING_SHOOTING_FORWARD;

				if (fireButton)
				{
					animation = &runShoot;
				}
				else
				{
					animation = &run;
				}
			}
		}
		else
		{
			if (upButton)
			{
				orientation = STANDING_SHOOTING_UP;
				animation = &shootStraightUp;
			}
			else if (downButton)
			{
				orientation = PRONE;
				animation = &layDown;
			}
			else
			{
				orientation = STANDING;
				animation = &stand;
			}
		}
		
		if (animation)
		{
			setShape(animation->getCurrentFrame(theGame.time));
		}
		else
		{
			cerr << "Animation not set" << endl;
		}

		if (fireButton && gunLoaded)
		{
			vec2 bulletOffset;
			vec2 bulletVelocity;

			switch (orientation)
			{
			default:
			case STANDING:
				bulletOffset = vec2(10, 25);
				bulletVelocity = vec2(bulletSpeed, 0);
				break;
			case PRONE:
				bulletOffset = vec2(10, 10);
				bulletVelocity = vec2(bulletSpeed, 0);
				break;
			case STANDING_SHOOTING_UP:
				bulletOffset = vec2(2, 40); 
				bulletVelocity = vec2(0, bulletSpeed);
				break;
			case RUNNING_SHOOTING_FORWARD:
				bulletOffset = vec2(10, 25);
				bulletVelocity = vec2(bulletSpeed, 0);
				break;
			case RUNNING_SHOOTING_UP:
				bulletOffset = vec2(10, 36);
				bulletVelocity = vec2(bulletSpeed, bulletSpeed / 2);
				break;
			case RUNNING_SHOOTING_DOWN:
				bulletOffset = vec2(10, 16);
				bulletVelocity = vec2(bulletSpeed, -bulletSpeed / 2);
				break;
			case JUMPING_SHOOTING_UP:
				bulletOffset = vec2(0, 10);
				bulletVelocity = vec2(0, bulletSpeed / 2);
				break;
			case JUMPING_SHOOTING_UP_FORWARD:
				bulletOffset = vec2(0, 10);
				bulletVelocity = vec2(bulletSpeed,  bulletSpeed / 2);
				break;
			case JUMPING_SHOOTING_FORWARD:
				bulletOffset = vec2(0, 10);
				bulletVelocity = vec2(bulletSpeed,  0);
				break;
			case JUMPING_SHOOTING_DOWN_FORWARD:
				bulletOffset = vec2(0, 10);
				bulletVelocity = vec2(bulletSpeed,  -bulletSpeed / 2);
				break;
			case JUMPING_SHOOTING_DOWN:
				bulletOffset = vec2(0, 10);
				bulletVelocity = vec2(velocity.x + 0,  -bulletSpeed);
				break;

			}


			if (facingLeft) {
				bulletOffset.x *= -1;
				bulletVelocity.x *= -1;
			}

			Bullet::shoot(position + bulletOffset, bulletVelocity);
			gunLoaded = false;
			reloadTime = 1.0 / fireRate;
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

		run.addFrame(makeShape(0, 6, 19, 36));
		run.addFrame(makeShape(37, 6, 24, 37));
		run.addFrame(makeShape(77, 6, 24, 37));
		run.addFrame(makeShape(115, 6, 24, 37));
		run.addFrame(makeShape(157, 6, 24, 37));

		runShoot.addFrame(makeShape(235, 6, 24, 37));
		runShoot.addFrame(makeShape(235, 86, 24, 37));
		runShoot.addFrame(makeShape(272, 86, 24, 37));

		runShootUp.addFrame(makeShape(0, 128, 19, 36));
		runShootUp.addFrame(makeShape(31, 128, 24, 37));
		runShootUp.addFrame(makeShape(67, 128, 24, 37));

		// It's ok for an animation to have just one frame.
		shootStraightUp.addFrame(makeShape(319, 0, 24, 45));

		layDown.addFrame(makeShape(271, 13, 37, 18));

		runShootDown.addFrame(makeShape(305, 86, 24, 37));
		runShootDown.addFrame(makeShape(335, 86, 24, 37));
		runShootDown.addFrame(makeShape(362, 85, 24, 37));

		stand.addFrame(makeShape(196, 6, 24, 37));

		jumpAnimation.addFrame(makeShape(0, 51, 24, 24));
		jumpAnimation.addFrame(makeShape(41, 51, 24, 24));
		jumpAnimation.addFrame(makeShape(80, 51, 24, 24));
		jumpAnimation.addFrame(makeShape(120, 51, 24, 24));

		deathFlip.addFrame(makeShape(155, 53, 28, 19));
		deathFlip.addFrame(makeShape(198, 50, 23, 25));
		deathFlip.addFrame(makeShape(155, 53, 28, 19));
		deathFlip.addFrame(makeShape(276, 53, 28, 21));

		deadAnimation.addFrame(makeShape(311, 56, 41, 14));



	}

};

