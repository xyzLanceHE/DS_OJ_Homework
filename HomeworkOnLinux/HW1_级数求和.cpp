// 1853760 贺兰山
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

//#define ACTIVE
#ifdef ACTIVE
#define MAIN int main()
#else
#define MAIN static int test()
#endif

class HugeUnsignedInt
{
public:
	HugeUnsignedInt(std::string& valStr);
	HugeUnsignedInt operator*(const HugeUnsignedInt& other) const;
	HugeUnsignedInt operator+(const HugeUnsignedInt& other) const;
	std::string ToString() const;
private:
	std::string data;
};


MAIN
{
	char buf[128];
	while (true)
	{
		std::cin.getline(buf, 128);
		std::stringstream ss(buf);
		int A, N;
		ss >> N >> A;
		if (N == 0)
		{
			std::cout << "0\n";
		}
		else
		{
			std::string zero("0");
			std::string AString = std::to_string(A);
			std::string IString;
			HugeUnsignedInt iA(AString);
			HugeUnsignedInt iA0(AString);
			HugeUnsignedInt val(zero);
			for (int i = 1; i <= N; i++)
			{
				IString = std::to_string(i);
				HugeUnsignedInt ii(IString);
				val = val + ii * iA;
				iA = iA * iA0;
			}
			std::cout << val.ToString() << std::endl;
		}

		

		if (std::cin.eof())
		{
			break;
		}
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

HugeUnsignedInt HugeUnsignedInt::operator+(const HugeUnsignedInt& other) const
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
	size_t longerLen = std::max(this->data.size(), other.data.size());
	size_t shorterLen = 0;
	std::vector<char>* longerVal = nullptr;
	if (this->data.size() > other.data.size())
	{
		shorterLen = other.data.size();
		longerVal = &thisVal;
	}
	else
	{
		shorterLen = this->data.size();
		longerVal = &otherVal;
	}
	std::vector<char> resultBuf(longerLen + 1);
	for (size_t i = 0; i < shorterLen; i++)
	{
		resultBuf[i] += thisVal[i] + otherVal[i];
		resultBuf[i + 1] += resultBuf[i] / 10;
		resultBuf[i] = resultBuf[i] % 10;
	}
	for (size_t i = shorterLen; i < longerLen; i++)
	{
		resultBuf[i] += (*longerVal)[i];
		resultBuf[i + 1] += resultBuf[i] / 10;
		resultBuf[i] = resultBuf[i] % 10;
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
