// 贺兰山 1853760

#include <iostream>
#include <iomanip>
#include <string>

#ifdef ACTIVE
#define MAIN int main()
#else
#define MAIN static int test()
#endif

MAIN
{
	constexpr int bufLen = 1024;
	char buf[bufLen];

	bool isFirstLine = true;
	while (true)
	{
		std::cin.get(buf[0]);
		if (buf[0] == '#')
		{
			break;
		}
		std::cin.getline(buf + 1, 1023);
		//std::string line(buf);
		if (isFirstLine)
		{
			isFirstLine = false;
			// std::cout << std::endl;
		}
		else
		{
			std::cout << std::endl;
		}
		long long checksum = 0;
		int pos = 0;
		for (auto c : buf)
		{
			pos++;
			if (c >= 'A' && c <= 'Z')
			{
				checksum += (c - 'A' + 1) * pos;
			}
			else if(c != ' ')
			{
				break;
			}
		}
		std::cout << checksum;
	}

	return 0;
}