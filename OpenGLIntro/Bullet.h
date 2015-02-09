#pragma once
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "Animation.h"
#include "C:\Users\navarre.luce\Documents\GitHub\NLuceGameEngine\NLuceGameEngine\Sprite.h"

class Bullet :
	public Sprite
{
public:
	Bullet();
	~Bullet();

	int speed = 300;

	Texture* bulletSpriteSheet;

	Animation normalBullet;

	std::vector<Shape *> shapesToDelete;


	Shape * makeShape(int left, int top, int width, int height)
	{
		Shape * shape = new Shape(bulletSpriteSheet, left, top, width, height, CENTER, false);
		shapesToDelete.push_back(shape);
		return shape;
	}

	void init()
	{
		bulletSpriteSheet = new Texture("NormalBulet.png");
		bulletSpriteSheet->filterNearest();

		normalBullet.addFrame(makeShape(0, 0, 3, 3));

	}
};

