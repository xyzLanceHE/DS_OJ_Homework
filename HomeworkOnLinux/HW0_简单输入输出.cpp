// 贺兰山 1853760

#include <iostream>
#include <iomanip>

#ifdef ACTIVE
#define MAIN int main()
#else
#define MAIN static int test()
#endif

MAIN
{
	double sum = 0.0;
	double income = 0.0;
	//constexpr int bufLen = 1024;
	//char buf[bufLen];
	for (int _ = 0; _ < 12; _++)
	{
		std::cin >> income;
		sum += income; 
	}
	std::cout << "¥" << std::fixed << std::setprecision(2) << (sum / 12) << std::endl;
	return 0;
}