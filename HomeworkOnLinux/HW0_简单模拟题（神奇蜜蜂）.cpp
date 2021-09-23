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
	using ulli = unsigned long long int;

	constexpr ulli specialFemaleBee = 1;

	while (true)
	{
		ulli maleBees = 0;
		ulli femaleBees = 0;
		ulli totalBees = 0;
		int year;
		std::cin >> year;
		if (year == -1)
		{
			break;
		}
		for (int _ = 0; _ < year; _++)
		{
			ulli newMaleBees = maleBees + femaleBees + specialFemaleBee;
			ulli newFemaleBees = maleBees;
			maleBees = newMaleBees;
			femaleBees = newFemaleBees;
		}
		totalBees = femaleBees + maleBees + specialFemaleBee;
		std::cout << maleBees << ' ' << totalBees << std::endl;

	}
	return 0;
}