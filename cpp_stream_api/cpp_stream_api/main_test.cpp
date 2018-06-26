#include "streamapi.h"



int main()
{

	std::vector<int> what = array_of<int>(1, 2, 3, 4, 5, 6,long(1));
	std::map<int,int> what2 = map_of<int, int>(std::make_pair(1, 1),std::make_pair(12, 2),std::make_pair(3,3));
	return 0;
}