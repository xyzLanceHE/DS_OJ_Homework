// 贺兰山 1853760
#include <iostream>
#include <string>
#include <vector>


#ifdef ACTIVE
#define MAIN int main()
class HugeUnsignedInt
{
public:
	HugeUnsignedInt(std::string& valStr);
	HugeUnsignedInt operator*(const HugeUnsignedInt& other) const;
	std::string ToString() const;
private:
	std::string data;
};


MAIN
{
	int round;
	std::cin >> round;
	for (int i = 0; i < round; i++)
	{
		std::string a, b;
		std::cin >> a >> b;
		HugeUnsignedInt ia(a), ib(b);
		std::cout << (ia * ib).ToString() << std::endl;
	}

	return 0;
}

HugeUnsignedInt::HugeUnsignedInt(std::string& valStr)
{
	this->data = valStr;
}

HugeUnsignedInt HugeUnsignedInt::operator*(const HugeUnsignedInt& other) const
{
	std::vector<char> thisVal(this->data.rbegin(), this->data.rend());
	std::vector<char> otherVal(other.data.rbegin(), other.data.rend());
	for (size_t i = 0; i < thisVal.size(); i++)
	{
		thisVal[i] -= '0';
	}
	for (size_t i = 0; i < otherVal.size(); i++)
	{
		otherVal[i] -= '0';
	}
	std::vector<char> resultBuf(thisVal.size() + otherVal.size() + 1);
	for (size_t i = 0; i < thisVal.size(); i++)
	{
		for (size_t j = 0; j < otherVal.size(); j++)
		{
			int product = thisVal[i] * otherVal[j];
			resultBuf[i + j] += product;
			resultBuf[i + j + 1] += resultBuf[i + j] / 10;
			resultBuf[i + j] = resultBuf[i + j] % 10;
		}
	}
	while (resultBuf.size() != 0 && *resultBuf.rbegin() == 0)
	{
		resultBuf.pop_back();
	}
	for (size_t i = 0; i < resultBuf.size(); i++)
	{
		resultBuf[i] += '0';
	}
	std::string result(resultBuf.rbegin(), resultBuf.rend());
	return HugeUnsignedInt(result);

}

std::string HugeUnsignedInt::ToString() const
{
	if (this->data == "")
	{
		return std::string("0");
	}
	else
	{
		return this->data;
	}
}

#else
#define MAIN static int test()
#endif

