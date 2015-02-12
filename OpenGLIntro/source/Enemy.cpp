#include "Enemy.h"
#include <vector>

Enemy::Enemy()
{
	init();
}


Enemy::~Enemy()
{
}

vector<Enemy*> Enemy::enemyList;
vec2 Enemy::playerPosition;
Texture * Enemy::enemySpriteSheet = 0;
Animation Enemy::run;
Animation Enemy::jump;
bool isDropping = false;
bool isRunning = false;

Enemy * Enemy::Spawn(const vec2 & position, const vec2 & velocity)
{
	// make a new Enemy
	Enemy * enemy = new Enemy();
	enemy->position = position;
	enemy->velocity = velocity;
	enemy->dead = false;

	// add it to the list
	enemyList.push_back(enemy);

	return enemy;
}

void Enemy::moveAll()
{
	//cout << enemyList.size() << endl;

	// move all the Enemys
	auto it = enemyList.begin();
	while (it < enemyList.end()){
		Enemy * enemy = *it;
		enemy->moveSprite();

		if (enemyList.size() > 20)
		{
			enemy->dead = true;
		}
		if (enemy->dead)
		{
			it = enemyList.erase(it);
			delete enemy;
		
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

