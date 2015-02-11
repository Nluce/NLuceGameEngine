#pragma once
#include "Sprite.h"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "Animation.h"
#include "Shape.h"
#include <time.h>


class Enemy :
	public Sprite
{
public:
	Enemy();
	~Enemy();
	int speed = 100;
	double gravity = 250.0f;
	bool dead = false;
	bool isOnPlatform = false;
	bool isDropping = true;
	static Texture * enemySpriteSheet;
	static Animation run;
	std::vector<Shape *> shapesToDelete;
	int speed = 100;
	vec2 preMove;
	vec2 postMove;

	

	static void Enemy::Spawn(const vec2 & position, const vec2 & velocity);
	static void moveAll(float elapsedTime);
	static void drawAll(const mat4 & matrixIn, int matrixUniformID);

	Shape * makeShape(int left, int top, int width, int height)
	{
		Shape * shape = new Shape(enemySpriteSheet, left, top, width, height, BOTTOM_CENTER, false);
		shapesToDelete.push_back(shape);
		return shape;
	}
	
	void init()
	{
		if (!enemySpriteSheet)
		{
			enemySpriteSheet = new Texture("ContraEnemySheet.png");
			enemySpriteSheet->filterNearest();

			

			run.addFrame(makeShape(154, 47, 17, 31));
			run.addFrame(makeShape(174, 45, 18, 34));
			run.addFrame(makeShape(195, 46, 20, 33));
			run.addFrame(makeShape(218, 47, 16, 32));
			run.addFrame(makeShape(237, 44, 19, 35));
			run.addFrame(makeShape(260, 45, 20, 34));
		}
	}

	void checkOnPlatform()
	{
		if (!isDropping)
		{
			for (vec3 platform : theGame.map->platformList)
			{
				if (preMove.x > platform.x && preMove.x < platform.z)
				{
					if (preMove.y >= platform.y && postMove.y < platform.y)
					{
						isOnPlatform = true;
						velocity.y = 0;
						position.y = platform.y;
					}
				}
			}
		}
	}

	void moveSprite(float elapsedTime)
	{
		float time = (float)(clock()) / CLOCKS_PER_SEC;

		setShape(run.getCurrentFrame(time));

		if (!dead)
		{
			velocity.y -= gravity * elapsedTime;
			velocity.x = speed;

			preMove = position;
			postMove = preMove + velocity * elapsedTime;
			checkOnPlatform();
			position += velocity * elapsedTime;
			// if (something were to kill this dude...)

			{
				//dead = true;
			}
		}

	}

	
};


