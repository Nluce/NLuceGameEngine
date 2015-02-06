#pragma once

#include "Shape.h"

#include <vector>
#include <iostream>

class Animation {
	// frames is a vector (list) of Shape pointers
	std::vector<Shape *> frames;

public:
	float framesPerSecond = 10.0f;

	Animation(){}

	void addFrame(Shape* frame)
	{
		frames.push_back(frame);
	}

	Shape * getCurrentFrame(float timeInSeconds)
	{
		int size = frames.size();
		if (size < 1)
		{
			std::cerr << "Animation has no frames" << std::endl;
			return 0;
		}
		int frameIndex = int(timeInSeconds * framesPerSecond) % size;
		return frames[frameIndex];
	}

};