#include "Enemy.h"
#include <vector>

Enemy::Enemy()
{
	init();
}


Enemy::~Enemy()
{
}

vector<Enemy*> enemyList;

Texture * Enemy::enemySpriteSheet = 0;
Shape * Enemy::enemyShape = 0;


void Enemy::Spawn(const vec2 & position, const vec2 & velocity)
{
	// make a new Enemy
	Enemy * Enemy = new Enemy();
	Enemy->position = position;
	Enemy->velocity = velocity;


	// add it to the list
	enemyList.push_back(Enemy);



}

void Enemy::moveAll(float elapsedTime)
{
	// move all the Enemys
	auto it = enemyList.begin();
	while (it < enemyList.end()){
		Enemy * Enemy = *it;
		Enemy->moveSprite(elapsedTime);
		if (Enemy->dead)
		{
			it = enemyList.erase(it);
			delete Enemy;
		
		}
		else
		{
			it++;
		}
	}

}

void Enemy::drawAll(const mat4 & matrixIn, int matrixUniformID)
{
	// draw all the Enemys
	for (Enemy * Enemy : enemyList)
	{
		if (!Enemy->dead)
		{
			Enemy->draw(matrixIn, matrixUniformID);
		}
	}
}

