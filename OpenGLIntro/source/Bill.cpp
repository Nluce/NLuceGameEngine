#include "Bill.h"





Bill::~Bill()
{
	delete contraSpriteSheet;
	delete contraRunFrame1;
	delete contraRunFrame2;
	delete contraRunFrame3;
	delete contraRunFrame4;
	delete contraRunFrame5;
	delete contraStandFrame;
	delete contraJumpFrame1;
	delete contraJumpFrame2;
	delete contraJumpFrame3;
	delete contraJumpFrame4;
}
