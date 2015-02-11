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
#include "Game.h"

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
	bool isDropping = false;

	static Texture * enemySpriteSheet;
	static Animation run;
	static vector<Enemy*> enemyList;

	std::vector<Shape *> shapesToDelete;

	vec2 preMove;
	vec2 postMove;

	

	static Enemy * Enemy::Spawn(const vec2 & position, const vec2 & velocity);
	static void moveAll();
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

	void moveSprite()
	{

		setShape(run.getCurrentFrame(theGame.time));

		if (!dead)
		{
			static const int edge = 10;
			velocity.y -= gravity * theGame.elapsedTime;

			if (position.x > theGame.mapSize.x - edge) {
				mirror = true;
			}
			else if (position.x < 0 + edge) {
				mirror = false;
			}

			velocity.x = mirror ? -speed : speed;

			preMove = position;
			postMove = preMove + velocity * theGame.elapsedTime;
			checkOnPlatform();

			if (position.y < 0)
			{
				// on ground
				position.y = 0;
				velocity.y = 0;
			}
			position += velocity * theGame.elapsedTime;
			// if (something were to kill this dude...)

			{
				//dead = true;
			}
		}

	}

	
};


