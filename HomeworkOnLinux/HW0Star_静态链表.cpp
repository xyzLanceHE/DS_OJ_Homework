// 贺兰山 1853760
#include <iostream>
#include <stdexcept>

// 80分上不去了，也不知道错哪了
// 有空再写


//#define ACTIVE
#ifdef ACTIVE
#define MAIN int main()
#else
#define MAIN static int test()
#endif


template<typename TValue>
// 需要重载运算符 ostream << TValue
class StaticLinkedList
{
public:
	using ErrorType = int;
	static constexpr ErrorType FULL = -1;
	static constexpr ErrorType EMPTY = -2;
	static constexpr ErrorType INVALID = -3;
public:
	StaticLinkedList(int arraySize);
	~StaticLinkedList();
	void PrintContent();
	void PrintDetail();
	void Insert(int index, TValue& val);
	void Append(TValue& val);
	TValue Remove(int index);
	int Find(TValue& val);
private:
	struct StaticNode
	{
	public:
		TValue* pValue;
		int NextIndex;
	public:
		StaticNode(TValue& val, int next);
		StaticNode(int next);
		StaticNode();
		~StaticNode();
	};
	StaticNode* pData;
	int ValueTail;
	int SpareTail;
	int ArraySize;
	static constexpr int ValueHead = 0;
	static constexpr int SpareHead = 1;
};

template class StaticLinkedList<std::string>;
using StringList = StaticLinkedList<std::string>;

MAIN
{
	int m ,n;
	std::cin >> m >> n;
	StringList list(m);
	std::string val;
	
	for (int i = 0; i < n; i++)
	{
		try
		{
			std::cin >> val;
			list.Append(val);
		}
		catch (StringList::ErrorType e)
		{

		}
	}

	list.PrintDetail();

	//插入
	int insertPosition;
	std::cin >> insertPosition >> val;
	try
	{
		list.Insert(insertPosition, val);
		list.PrintContent();
	}
	catch (StringList::ErrorType e)
	{
		switch (e)
		{
		case StringList::FULL:
			std::cout << "FULL\n";
			break;
		case StringList::INVALID:
			std::cout << -1 << std::endl;
			break;
		default:
			std::cout << "fuck\n";
			break;
		}
	}

	//删除
	int removePosition;
	std::cin >> removePosition;
	try
	{
		std::string removedVal = list.Remove(removePosition);
		std::cout << removedVal << std::endl;
	}
	catch (StringList::ErrorType e)
	{
		switch (e)
		{
		case StringList::EMPTY:
			std::cout << "EMPTY\n";
			break;
		case StringList::INVALID:
			std::cout << -1 << std::endl;
			break;
		default:
			std::cout << "fuck\n";
			break;
		}
	}

	//查找
	std::cin >> val;
	std::cout << list.Find(val) << std::endl;

	//追加
	std::cin >> val;
	try
	{
		list.Append(val);
		list.PrintContent();
	}
	catch (StringList::ErrorType e)
	{
		switch (e)
		{
		case StringList::FULL:
			std::cout << "FULL\n";
			break;
		default:
			std::cout << "fuck\n";
			break;
		}
	}

	list.PrintDetail();

	return 0;
}

template<typename TValue>
StaticLinkedList<TValue>::StaticLinkedList(int arraySize)
{
	if (arraySize <= 1)
	{
		this->pData = nullptr;
		return;
	}
	this->pData = new StaticNode[arraySize];
	for (int i = 1; i < arraySize - 1; i++)
	{
		this->pData[i].NextIndex = i + 1;
	}
	this->pData[arraySize - 1] = -1;
	this->ValueTail = ValueHead;
	this->SpareTail = arraySize - 1;
	this->ArraySize = arraySize;
}

template<typename TValue>
StaticLinkedList<TValue>::~StaticLinkedList()
{
	delete[] this->pData;
}

template<typename TValue>
void StaticLinkedList<TValue>::PrintContent()
{
	if (this->pData[ValueHead].NextIndex == -1)
	{
		std::cout << "EMPTY" << std::endl;
		return;
	}

	int index = ValueHead;
	while (this->pData[index].NextIndex != -1)
	{
		index = this->pData[index].NextIndex;
		std::cout << *this->pData[index].pValue << " ";
	}
	std::cout << std::endl;
}

template<typename TValue>
void StaticLinkedList<TValue>::PrintDetail()
{
	for (int i = 0; i < this->ArraySize; i++)
	{
		if (this->pData[i].pValue == nullptr)
		{
			std::cout << i << " : N/A : " << this->pData[i].NextIndex;
		}
		else
		{
			std::cout << i << " : " << *this->pData[i].pValue << " : " << this->pData[i].NextIndex;
		}
		if ((i + 1) % 3 == 0 || i == this->ArraySize - 1)
		{
			std::cout << std::endl;
		}
		else
		{
			std::cout << "\t\t";
		}
	}
}

template<typename TValue>
void StaticLinkedList<TValue>::Insert(int index, TValue& val)
{
	int firstSpare = this->pData[SpareHead].NextIndex;
	if (firstSpare == -1)
	{
		throw FULL;
	}
	int arrayIndex = ValueHead;
	for (int i = 0; i < index - 1; i++)
	{
		if (arrayIndex == -1)
		{
			throw INVALID;
		}
		arrayIndex = this->pData[arrayIndex].NextIndex;
	}
	delete this->pData[firstSpare].pValue;
	this->pData[firstSpare].pValue = nullptr;
	this->pData[firstSpare].pValue = new TValue(val);
	this->pData[SpareHead].NextIndex = this->pData[firstSpare].NextIndex;
	this->pData[firstSpare].NextIndex = this->pData[arrayIndex].NextIndex;
	this->pData[arrayIndex].NextIndex = firstSpare;
	if (firstSpare == this->SpareTail)
	{
		this->SpareTail = SpareHead;
	}
}

template<typename TValue>
void StaticLinkedList<TValue>::Append(TValue& val)
{
	int firstSpare = this->pData[SpareHead].NextIndex;
	if (firstSpare == -1)
	{
		throw FULL;
	}
	delete this->pData[firstSpare].pValue;
	this->pData[firstSpare].pValue = nullptr;
	this->pData[firstSpare].pValue = new TValue(val);
	this->pData[SpareHead].NextIndex = this->pData[firstSpare].NextIndex;
	this->pData[ValueTail].NextIndex = firstSpare;
	this->ValueTail = firstSpare;
	this->pData[firstSpare].NextIndex = -1;
	if (firstSpare == this->SpareTail)
	{
		this->SpareTail = SpareHead;
	}
}

template<typename TValue>
TValue StaticLinkedList<TValue>::Remove(int index)
{
	if (this->pData[ValueHead].NextIndex == -1)
	{
		throw EMPTY;
	}
	int arrayIndex = ValueHead;
	for (int i = 0; i < index - 1; i++)
	{
		if (arrayIndex == -1)
		{
			throw INVALID;
		}
		arrayIndex = this->pData[arrayIndex].NextIndex;		
	}
	int indexToRemove = this->pData[arrayIndex].NextIndex;
	if (indexToRemove == -1)
	{
		throw INVALID;
	}
	TValue valRemoved = TValue(*this->pData[indexToRemove].pValue);
	delete this->pData[indexToRemove].pValue;
	this->pData[indexToRemove].pValue = nullptr;
	this->pData[arrayIndex].NextIndex = this->pData[indexToRemove].NextIndex;
	if (indexToRemove == this->ValueTail)
	{
		this->ValueTail = arrayIndex;
	}
	int spareNext = this->pData[SpareHead].NextIndex;
	this->pData[SpareHead].NextIndex = indexToRemove;
	this->pData[indexToRemove].NextIndex = spareNext;
	return valRemoved;
}

template<typename TValue>
int StaticLinkedList<TValue>::Find(TValue& val)
{
	int position = 0;
	int index = this->ValueHead;
	while (this->pData[index].NextIndex != -1)
	{
		index = this->pData[index].NextIndex;
		position++;
		TValue* p = this->pData[index].pValue;
		if (p != nullptr)
		{
			if (val == *p)
			{
				return position;
			}
		}
	}
	return -1;
}

template<typename TValue>
StaticLinkedList<TValue>::StaticNode::StaticNode(TValue& val, int next)
{
	this->pValue = new TValue(val);
	this->NextIndex = next;
}

template<typename TValue>
StaticLinkedList<TValue>::StaticNode::StaticNode(int next)
{
	this->pValue = nullptr;
	this->NextIndex = next;
}

template<typename TValue>
StaticLinkedList<TValue>::StaticNode::StaticNode()
{
	this->pValue = nullptr;
	this->NextIndex = -1;
}

template<typename TValue>
StaticLinkedList<TValue>::StaticNode::~StaticNode()
{
	delete this->pValue;
}
