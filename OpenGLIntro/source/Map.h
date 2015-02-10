
#include <glm/glm.hpp>
#include <vector>

using namespace glm;
using namespace std;

class Map
{

public:
	int mapHeight = 2159;
	vector<vec3> platformList;

	void addPlatform(int left, int top, int right)
	{
		platformList.push_back(vec3(left, mapHeight - top, right));
	}

	Map()
	{
		addPlatform(0, 2125, 256);
		addPlatform(160, 2092, 256);
		addPlatform(128, 2059, 222);
		addPlatform(0, 1996, 127);
		addPlatform(160, 1996, 256);
		addPlatform(32, 1965, 95);
		addPlatform(128, 1949, 256);
		addPlatform(96, 2028, 222);

		addPlatform(0, 1933, 64);

		addPlatform(192, 1917, 256);

		addPlatform(64, 1901, 159);

		addPlatform(0, 1870, 127);

		addPlatform(32, 1837, 191);

		addPlatform(0, 1805, 64);

		addPlatform(192, 1805, 256);

		addPlatform(32, 1758, 64);

		addPlatform(128, 1758, 256);

		addPlatform(32, 1725, 96);

		addPlatform(0, 1694, 128);

		addPlatform(160, 1678, 256);

		addPlatform(0, 1645, 256);

		addPlatform(0, 1597, 64);

		addPlatform(0, 1548, 128);

		addPlatform(32, 1485, 96);

		addPlatform(64, 1518, 256);

		addPlatform(128, 1453, 256);

		addPlatform(32, 1420, 128);

		addPlatform(0, 1390, 64);

		addPlatform(0, 1341, 256);
		//missed this first time
		addPlatform(192, 1310, 256);

		addPlatform(160, 1278, 256);
		// this too
		addPlatform(0, 1264, 64);

		addPlatform(128, 1245, 223);

		addPlatform(32, 1230, 96);

		addPlatform(0, 1197, 64);

		addPlatform(192, 1182, 256);

		addPlatform(32, 1132, 128);

		addPlatform(160, 1132, 256);

		addPlatform(0, 1102, 96);

		addPlatform(160, 1036, 192);

		addPlatform(128, 989, 192);

		addPlatform(160, 958, 223);

		addPlatform(0, 926, 32);

		addPlatform(64, 926, 160);

		addPlatform(128, 894, 192);

		addPlatform(64, 846, 223);

		addPlatform(32, 814, 128);

		addPlatform(64, 767, 160);

		addPlatform(192, 767, 256);

		addPlatform(192, 733, 223);

		addPlatform(160, 702, 256);

		addPlatform(32, 687, 128);

		addPlatform(0, 638, 96);

		addPlatform(192, 558, 256);

		addPlatform(161, 526, 256);

		addPlatform(0, 494, 223);

		addPlatform(128, 462, 256);

		addPlatform(0, 446, 96);

		addPlatform(96, 414, 190);

		addPlatform(0, 382, 128);

		addPlatform(160, 366, 256);

		addPlatform(32, 334, 96);

		addPlatform(128, 300, 256);

		addPlatform(0, 255, 256);

		addPlatform(0, 207, 256);

	}

};