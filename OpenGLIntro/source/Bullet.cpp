#include "Bullet.h"


#include <vector>


Bullet::Bullet()
{
	init();
}


Bullet::~Bullet()
{
}


vector<Bullet *> Bullet::bulletList;



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
}

void Bullet::moveAll()
{
	// move all the bullets
	auto it = bulletList.begin();
	while (it < bulletList.end() ){
		Bullet * bullet = *it;
		bullet->moveSprite();
		if (bullet->dead)
		{
			it = bulletList.erase(it);
			delete bullet;
		}
		else
		{
			it++;
		}
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
