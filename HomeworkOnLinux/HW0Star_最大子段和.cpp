// 贺兰山 1853760
#include <iostream>

#ifdef ACTIVE
#define MAIN int main()
#else
#define MAIN static int test()
#endif

MAIN
{
    int len;
    std::cin >> len;
    long long currentSum = 0;
    long long maxSum = 0;
    long long num;
    for (int i = 0; i < len; i++)
    {
        std::cin >> num;
        currentSum += num;
        if (currentSum < 0)
        {
            currentSum = 0;
        }
        else if (currentSum > maxSum)
        {
            maxSum = currentSum;
        }

    }
    std::cout << maxSum << std::endl;

    return 0;
}