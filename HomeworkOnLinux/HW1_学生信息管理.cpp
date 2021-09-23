// 1853760 贺兰山
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

//#define ACTIVE
#ifdef ACTIVE
#define MAIN int main()
#else
#define MAIN static int test()
#endif

struct StudentInfo
{
public:
	std::string ID;
	std::string Name;
	StudentInfo(std::string& id, std::string& name)
	{
		this->ID = id;
		this->Name = name;
	}
};


MAIN
{
	std::vector<StudentInfo> list;
int n;
std::cin >> n;
std::string id, name;
for (int i = 0; i < n; i++)
{
	std::cin >> id >> name;
	list.emplace_back(id, name);
}
std::string cmd;
while (true)
{
	std::cin >> cmd;
	if (cmd == "insert")
	{
		int index;
		std::cin >> index >> id >> name;
		if (index <= list.size() + 1 && index >= 1)
		{
			std::cout << "0\n";
			list.insert(list.begin() + index -1, { id, name });
		}
		else
		{
			std::cout << "-1\n";
		}
	}
	else if (cmd == "remove")
	{
		int index;
		std::cin >> index;
		if (index <= list.size() && index >= 1)
		{
			std::cout << "0\n";
			list.erase(list.begin() + index - 1);
		}
		else
		{
			std::cout << "-1\n";
		}
	}
	else if (cmd == "check")
	{
		std::cin >> cmd;
		if (cmd == "name")
		{
			std::string nameToFind;
			std::cin >> nameToFind;
			bool found = false;
			for (int i=0;i<list.size();i++)
			{
				if (list[i].Name == nameToFind)
				{
					found = true;
					std::cout << i + 1 << " " << list[i].ID << " " << list[i].Name << std::endl;
					break;
				}
			}
			if (!found)
			{
				std::cout << "-1\n";
			}
		}
		else if (cmd == "no")
		{
			std::string numberToFind;
			std::cin >> numberToFind;
			bool found = false;
			for (int i = 0; i < list.size(); i++)
			{
				if (list[i].ID == numberToFind)
				{
					found = true;
					std::cout << i + 1 << " " << list[i].ID << " " << list[i].Name << std::endl;
					break;
				}
			}
			if (!found)
			{
				std::cout << "-1\n";
			}
		}
	}
	else if (cmd == "end")
	{
		std::cout << list.size() << std::endl;
		break;
	}
}
	return 0;
}