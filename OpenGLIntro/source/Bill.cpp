#include "Bill.h"





Bill::~Bill()
{
	for each (Shape* shape in shapesToDelete)
	{
		delete shape;
	}
	shapesToDelete.clear();
}
