#pragma once
#include "C:\Users\navarre.luce\Documents\GitHub\NLuceGameEngine\NLuceGameEngine\Sprite.h"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "Animation.h"
#include "Shape.h"
class Enemy :
	public Sprite
{
public:
	Enemy();
	~Enemy();
	int speed = 100;
	int mapHeight = 2159;
	vec3 platformList[66];
	bool dead = false;

	static Texture * enemySpriteSheet;
	Animation run;
	std::vector<Shape *> shapesToDelete;

	Shape * makeShape(int left, int top, int width, int height)
	{
		Shape * shape = new Shape(enemySpriteSheet, left, top, width, height, BOTTOM_CENTER, false);
		shapesToDelete.push_back(shape);
		return shape;
	}
	Shape * makeMirrorShape(Shape * origionalShape)
	{
		Shape * shape = new Shape(origionalShape, true);
		shapesToDelete.push_back(shape);
		return shape;
	}

	void init()
	{
		enemySpriteSheet = new Texture("ContraEnemySheet.png");
		enemySpriteSheet->filterNearest();

		run.addFrame(makeShape(154, 47, 17, 31));
		run.addFrame(makeShape(174, 45, 18, 34));
		run.addFrame(makeShape(195, 46, 20, 33));
		run.addFrame(makeShape(218, 47, 16, 32));
		run.addFrame(makeShape(237, 44, 19, 35));
		run.addFrame(makeShape(260, 45, 20, 34));



		platformList[0] = vec3(0, mapHeight - 2125, 256);
		platformList[1] = vec3(160, mapHeight - 2092, 256);
		platformList[2] = vec3(128, mapHeight - 2059, 222);
		platformList[3] = vec3(0, mapHeight - 1996, 127);
		platformList[4] = vec3(160, mapHeight - 1996, 256);
		platformList[5] = vec3(32, mapHeight - 1965, 95);
		platformList[6] = vec3(128, mapHeight - 1949, 256);
		platformList[7] = vec3(96, mapHeight - 2028, 222);

		platformList[8] = vec3(0, mapHeight - 1933, 64);

		platformList[9] = vec3(192, mapHeight - 1917, 256);

		platformList[10] = vec3(64, mapHeight - 1901, 159);

		platformList[11] = vec3(0, mapHeight - 1870, 127);

		platformList[12] = vec3(32, mapHeight - 1837, 191);

		platformList[13] = vec3(0, mapHeight - 1805, 64);

		platformList[14] = vec3(192, mapHeight - 1805, 256);

		platformList[15] = vec3(32, mapHeight - 1758, 64);

		platformList[16] = vec3(128, mapHeight - 1758, 256);

		platformList[17] = vec3(32, mapHeight - 1725, 96);

		platformList[18] = vec3(0, mapHeight - 1694, 128);

		platformList[19] = vec3(160, mapHeight - 1678, 256);

		platformList[20] = vec3(0, mapHeight - 1645, 256);

		platformList[21] = vec3(0, mapHeight - 1597, 64);

		platformList[22] = vec3(0, mapHeight - 1548, 128);

		platformList[23] = vec3(32, mapHeight - 1485, 96);

		platformList[24] = vec3(64, mapHeight - 1518, 256);

		platformList[25] = vec3(128, mapHeight - 1453, 256);

		platformList[26] = vec3(32, mapHeight - 1420, 128);

		platformList[27] = vec3(0, mapHeight - 1390, 64);

		platformList[28] = vec3(0, mapHeight - 1341, 256);
		//missed this first time
		platformList[63] = vec3(192, mapHeight - 1310, 256);

		platformList[29] = vec3(160, mapHeight - 1278, 256);
		// this too
		platformList[64] = vec3(0, mapHeight - 1264, 64);

		platformList[30] = vec3(128, mapHeight - 1245, 223);

		platformList[31] = vec3(32, mapHeight - 1230, 96);

		platformList[32] = vec3(0, mapHeight - 1197, 64);

		platformList[33] = vec3(192, mapHeight - 1182, 256);

		platformList[34] = vec3(32, mapHeight - 1132, 128);

		platformList[35] = vec3(160, mapHeight - 1132, 256);

		platformList[36] = vec3(0, mapHeight - 1102, 96);

		platformList[37] = vec3(160, mapHeight - 1036, 192);

		platformList[38] = vec3(128, mapHeight - 989, 192);

		platformList[39] = vec3(160, mapHeight - 958, 223);

		platformList[40] = vec3(0, mapHeight - 926, 32);

		platformList[41] = vec3(64, mapHeight - 926, 160);

		platformList[42] = vec3(128, mapHeight - 894, 192);

		platformList[43] = vec3(64, mapHeight - 846, 223);

		platformList[44] = vec3(32, mapHeight - 814, 128);

		platformList[45] = vec3(64, mapHeight - 767, 160);

		platformList[46] = vec3(192, mapHeight - 767, 256);

		platformList[47] = vec3(192, mapHeight - 733, 223);

		platformList[48] = vec3(160, mapHeight - 702, 256);

		platformList[49] = vec3(32, mapHeight - 687, 128);

		platformList[50] = vec3(0, mapHeight - 638, 96);

		platformList[51] = vec3(192, mapHeight - 558, 256);

		platformList[52] = vec3(161, mapHeight - 526, 256);

		platformList[53] = vec3(0, mapHeight - 494, 223);

		platformList[54] = vec3(128, mapHeight - 462, 256);

		platformList[55] = vec3(0, mapHeight - 446, 96);

		platformList[56] = vec3(96, mapHeight - 414, 190);

		platformList[57] = vec3(0, mapHeight - 382, 128);

		platformList[58] = vec3(160, mapHeight - 366, 256);

		platformList[59] = vec3(32, mapHeight - 334, 96);

		platformList[60] = vec3(128, mapHeight - 300, 256);

		platformList[61] = vec3(0, mapHeight - 255, 256);

		platformList[62] = vec3(0, mapHeight - 207, 256);
	}

	
};

