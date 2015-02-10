#pragma once
#include "glm/glm.hpp"
#include "Map.h"


using namespace glm;


class Game
{
public:
	Map * map;
	vec2 mapSize;
};


extern Game theGame;