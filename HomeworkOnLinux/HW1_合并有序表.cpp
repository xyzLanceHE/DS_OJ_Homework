//Paste your code here
//NOTE: If you use java, your Main class must be named solution

#include <iostream>
#include <vector>
#include <algorithm>

//#define ACTIVE
#ifdef ACTIVE
#define MAIN int main()
#else
#define MAIN static int test()
#endif


MAIN
{
    std::vector<int> list;
    int a;
    while (true)
    {
        std::cin >> a;
        if (a == 0)
        {
            break;
        }
        list.push_back(a);
    }
    while (true)
    {
        std::cin >> a;
        if (a == 0)
        {
            break;
        }
        list.push_back(a);
    }
    std::sort(list.begin(), list.end());
    for (int i = 0; i < list.size(); i++)
    {
        std::cout << list[i] << " ";
    }
    return 0;


}