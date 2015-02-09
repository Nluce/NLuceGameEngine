#include "Bullet.h"


#include <vector>


Bullet::Bullet()
{
	init();
}


Bullet::~Bullet()
{
}


vector<Bullet *> bulletList;



Texture * Bullet::bulletSpriteSheet = 0;
Shape * Bullet::bulletShape = 0;


void Bullet::shoot(const vec2 & position, const vec2 & velocity)
{
	// make a new bullet
	Bullet * bullet = new Bullet();
	bullet->position = position;
	bullet->velocity = velocity;
	

	// add it to the list
	bulletList.push_back(bullet);


	cout << bulletList.size() << endl;

}

void Bullet::moveAll(float elapsedTime)
{
	vector<Bullet *> liveBullets;

	// move all the bullets
	for (Bullet * bullet : bulletList)
	{
		bullet->moveSprite(elapsedTime);
		if (bullet->dead)
		{
			delete bullet;
		} 
		else
		{
			liveBullets.push_back(bullet);
		}
	}

	bulletList.clear();
	for (Bullet * bullet : liveBullets)
	{
		bulletList.push_back(bullet);
	}

}

void Bullet::drawAll(const mat4 & matrixIn, int matrixUniformID)
{
	// draw all the bullets
	for (Bullet * bullet : bulletList)
	{
		if (!bullet->dead)
		{
			bullet->draw(matrixIn, matrixUniformID);
		}
	}
}
