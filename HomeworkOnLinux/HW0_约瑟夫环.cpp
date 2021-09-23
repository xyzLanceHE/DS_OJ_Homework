// 贺兰山 1853760
#include <iostream>
#include <sstream>
#include <vector>



#ifdef ACTIVE
#define MAIN int main()
#else
#define MAIN static int test()
#endif

int Josephus(int n, int m)
{

    if (n == 2)
    {
        return m % 2;
    }
    if (n == 1)
    {
        return 1;
    }
    // return (Josephus(n - 1, m) + m) % n;
    int result = Josephus(2, m);
    for (int i = 2; i < n; i++)
    {
        result = (result + m) % (i + 1);
    }
    return result;

}


MAIN
{
    char buf[128];

    while (true)
    {
        std::cin.getline(buf, 128);
        std::stringstream ss(buf);
        int n, m;
        ss >> n >> m;

        std::cout << Josephus(n, m) << std::endl;

        if (std::cin.eof())
        {
            break;
        }
    }

    return 0;
}