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
class Enemy :
	public Sprite
{
public:
	Enemy();
	~Enemy();
	int speed = 100;
	bool dead = false;

	static Texture * enemySpriteSheet;
	Animation run;
	std::vector<Shape *> shapesToDelete;

	void Enemy::Spawn(const vec2 & position, const vec2 & velocity);
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
		enemySpriteSheet = new Texture("ContraEnemySheet.png");
		enemySpriteSheet->filterNearest();

		run.addFrame(makeShape(154, 47, 17, 31));
		run.addFrame(makeShape(174, 45, 18, 34));
		run.addFrame(makeShape(195, 46, 20, 33));
		run.addFrame(makeShape(218, 47, 16, 32));
		run.addFrame(makeShape(237, 44, 19, 35));
		run.addFrame(makeShape(260, 45, 20, 34));
	}

	void moveSprite(float elapsedTime)
	{
		if (!dead)
		{
			position += velocity * elapsedTime;
			// if (something were to kill this dude...)
			{
				dead = true;
			}
		}

	}

	
};

