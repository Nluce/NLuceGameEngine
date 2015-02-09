#pragma once
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "Animation.h"
#include "Sprite.h"
#include "Game.h"

class Bullet :
	public Sprite
{
public:
	Bullet();
	~Bullet();


	int speed = 300;

	bool dead = false;

	static Texture * bulletSpriteSheet;
	static Shape * bulletShape;

	static void shoot(const vec2 & position, const vec2 & velocity);
	static void moveAll(float elapsedTime);
	static void drawAll(const mat4 & matrixIn, int matrixUniformID);

	void init()
	{
		if (!bulletSpriteSheet){
			bulletSpriteSheet = new Texture("NormalBulet.png");
			bulletSpriteSheet->filterNearest();
			bulletShape = new Shape(bulletSpriteSheet);
		}

		setShape(bulletShape);
	}


	void moveSprite(float elapsedTime)
	{
		if (!dead)
		{
			position += velocity * elapsedTime;
			if (position.x < 0 || position.y < 0 || position.x > theGame.mapSize.x || position.y > theGame.mapSize.y)
			{
				dead = true;
			}
		}
	}

};

