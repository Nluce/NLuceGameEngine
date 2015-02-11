#pragma once
#include "glm/glm.hpp"
#include "Map.h"
#include <time.h>

using namespace glm;


class Game
{
public:
	Map * map;
	vec2 mapSize;
	// the time since the beginning of the level
	float time = 0;
	// the time since the last frame
	float elapsedTime = 0;
	clock_t startTime;
	void startLevel()
	{
		startTime = clock();
		time = 0;
		elapsedTime = 0;
	}

	void startFrame()
	{
		float t = time;
		time = (float)(clock() - startTime) / CLOCKS_PER_SEC;
		elapsedTime = time - t;
	}
};


extern Game theGame;