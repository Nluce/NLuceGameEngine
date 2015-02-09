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

}

