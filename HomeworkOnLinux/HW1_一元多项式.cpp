// 1853760 贺兰山


#define ACTIVE
#ifdef ACTIVE

#include <iostream>

class PolyItem
{
public:
	int Coefficient;
	int Exponent;
};

class ExponentComparator
{
public:
	bool operator()(const PolyItem& left, const PolyItem& right);
};

class CoefficientComparator
{
public:
	bool operator()(const PolyItem& left, const PolyItem& right);
};

template<typename TValue>
class LinkedList
{
private:
	class LinkedListNode
	{
	public:
		TValue Value;
		LinkedListNode* Previous;
		LinkedListNode* Next;
	};

public:
	LinkedList();
	~LinkedList();
	// 复制
	LinkedList(LinkedList& other);
	// 移动
	LinkedList(LinkedList&& other);
	// 赋值
	LinkedList& operator=(LinkedList& other);
	LinkedList& operator=(LinkedList&& other);
	class LinkedListIterator;
	class ReversedLinkedListIterator;
	class LinkedListIterator
	{
	public:
		// 前置++, 使用前需要保证不是End(), 否则结果是未定义的, 后面类似
		LinkedListIterator& operator++() noexcept;
		// 前置--
		LinkedListIterator& operator--() noexcept;
		bool operator==(const LinkedListIterator& other) const noexcept;
		bool operator!=(const LinkedListIterator& other) const noexcept;
		TValue& operator*();
		TValue* operator->();
		operator ReversedLinkedListIterator();
		LinkedListIterator(ReversedLinkedListIterator& rIt);
	private:
		friend class LinkedList;
		friend class ReversedLinkedListIterator;
		LinkedListIterator(LinkedListNode* pItem);
		LinkedListNode* pItem;
	};
	class ReversedLinkedListIterator
	{
	public:
		// 前置++
		ReversedLinkedListIterator& operator++() noexcept;
		// 前置--
		ReversedLinkedListIterator& operator--() noexcept;
		bool operator==(const ReversedLinkedListIterator& other) const noexcept;
		bool operator!=(const ReversedLinkedListIterator& other) const noexcept;
		TValue& operator*();
		TValue* operator->();
		operator LinkedListIterator();
		ReversedLinkedListIterator(LinkedListIterator& it);
	private:
		friend class LinkedList;
		friend class LinkedListIterator;
		ReversedLinkedListIterator(LinkedListNode* pItem);
		LinkedListNode* pItem;
	};
	LinkedListIterator Begin();
	LinkedListIterator End();
	ReversedLinkedListIterator ReversedBegin();
	ReversedLinkedListIterator ReversedEnd();
	// 在it之前插入value, 并且返回指向插入的值的iterator
	LinkedListIterator Insert(TValue& value, LinkedListIterator&& it);
	// 移除it, 并且返回it原先的后继iterator
	LinkedListIterator Remove(LinkedListIterator&& it);
	// 查找value, 并且返回指向value的iterator, 如果找不到则返回End()
	template<typename TComparator>
	LinkedListIterator Find(TValue value, TComparator comparator);
	int Count();
private:
	LinkedListNode* pHead;
	LinkedListNode* pTail;
	int count;
};

template class LinkedList<PolyItem>;
using PolyString = LinkedList<PolyItem>;

// 不会改变p1和p2
PolyString AddTwoPoly(PolyString& p1, PolyString& p2);


int main()
{

	PolyString p1, p2;
	int n1, n2;
	std::cin >> n1;
	for (int i = 0; i < n1; i++)
	{
		int coef, exp;
		std::cin >> coef >> exp;
		PolyItem item = { coef, exp };
		p1.Insert(item, p1.End());
	}
	std::cin >> n2;
	for (int i = 0; i < n2; i++)
	{
		int coef, exp;
		std::cin >> coef >> exp;
		PolyItem item = { coef, exp };
		p2.Insert(item, p2.End());
	}

	int cmd;
	std::cin >> cmd;
	bool calSum = false;
	bool calProd = false;
	if (cmd == 0)
	{
		calSum = true;
	}
	else if (cmd == 1)
	{
		calProd = true;
	}
	else if (cmd == 2)
	{
		calSum = calProd = true;
	}

	if (calSum)
	{
		auto pSum = AddTwoPoly(p1, p2);
		for (auto it = pSum.Begin(); it != pSum.End(); ++it)
		{
			std::cout << it->Coefficient << " " << it->Exponent << " ";
		}
		std::cout << std::endl;
	}

	if (calProd)
	{
		// 将p1的每一项作用于p2, 再作加法
		// 复杂度大概n^3?
		// 空间复杂度常数
		PolyString pProd;
		
		for (auto it1 = p1.Begin(); it1 != p1.End(); ++it1)
		{
			PolyString p2Copy(p2);
			for (auto it2 = p2Copy.Begin(); it2 != p2Copy.End(); ++it2)
			{
				it2->Coefficient *= it1->Coefficient;
				it2->Exponent += it1->Exponent;
			}
			pProd = AddTwoPoly(pProd, p2Copy);
		}
		for (auto it = pProd.Begin(); it != pProd.End(); ++it)
		{
			std::cout << it->Coefficient << " " << it->Exponent << " ";
		}
		std::cout << std::endl;
	}
	
	return 0;
}


template<typename TValue>
LinkedList<TValue>::LinkedList()
{
	this->pHead = new LinkedListNode();
	this->pTail = new LinkedListNode();
	this->pHead->Next = this->pTail;
	this->pHead->Previous = nullptr;
	this->pTail->Next = nullptr;
	this->pTail->Previous = this->pHead;
	this->count = 0;
}

template<typename TValue>
LinkedList<TValue>::~LinkedList()
{
	LinkedListNode* follow = this->pHead;
	LinkedListNode* ahead = follow;
	while (ahead != nullptr)
	{
		ahead = ahead->Next;
		delete follow;
		follow = ahead;
	}
}

template<typename TValue>
LinkedList<TValue>::LinkedList(LinkedList& other)
{
	this->pHead = new LinkedListNode();
	this->pTail = new LinkedListNode();
	this->pHead->Next = this->pTail;
	this->pHead->Previous = nullptr;
	this->pTail->Next = nullptr;
	this->pTail->Previous = this->pHead;
	this->count = 0;
	for (auto it = other.Begin(); it != other.End(); ++it)
	{
		PolyItem item = *it;
		this->Insert(item, this->End());
	}
}

template<typename TValue>
LinkedList<TValue>::LinkedList(LinkedList&& other)
{
	this->pHead = other.pHead;
	this->pTail = other.pTail;
	this->count = other.count;
	other.pHead = other.pTail = nullptr;
}

template<typename TValue>
LinkedList<TValue>& LinkedList<TValue>::operator=(LinkedList& other)
{
	*this = std::move(other);
	return *this;
}

template<typename TValue>
LinkedList<TValue>& LinkedList<TValue>::operator=(LinkedList&& other)
{
	LinkedListNode* follow = this->pHead;
	LinkedListNode* ahead = follow;
	while (ahead != nullptr)
	{
		ahead = ahead->Next;
		delete follow;
		follow = ahead;
	}

	this->pHead = new LinkedListNode();
	this->pTail = new LinkedListNode();
	this->pHead->Next = this->pTail;
	this->pHead->Previous = nullptr;
	this->pTail->Next = nullptr;
	this->pTail->Previous = this->pHead;
	this->count = 0;
	for (auto it = other.Begin(); it != other.End(); ++it)
	{
		PolyItem item = *it;
		this->Insert(item, this->End());
	}
	return *this;
}

template<typename TValue>
typename LinkedList<TValue>::LinkedListIterator LinkedList<TValue>::Begin()
{
	return LinkedList<TValue>::LinkedListIterator(this->pHead->Next);
}

template<typename TValue>
typename LinkedList<TValue>::LinkedListIterator LinkedList<TValue>::End()
{
	return LinkedList<TValue>::LinkedListIterator(this->pTail);
}

template<typename TValue>
typename LinkedList<TValue>::ReversedLinkedListIterator LinkedList<TValue>::ReversedBegin()
{
	return LinkedList<TValue>::ReversedLinkedListIterator(this->pTail->Previous);
}

template<typename TValue>
typename LinkedList<TValue>::ReversedLinkedListIterator LinkedList<TValue>::ReversedEnd()
{
	return LinkedList<TValue>::ReversedLinkedListIterator(this->pHead);
}

template<typename TValue>
typename LinkedList<TValue>::LinkedListIterator LinkedList<TValue>::Insert(TValue& value, LinkedListIterator&& it)
{
	LinkedListNode* pre = it.pItem->Previous;
	LinkedListNode* next = it.pItem;
	LinkedListNode* node = new LinkedListNode();
	node->Value = value;
	node->Next = next;
	node->Previous = pre;
	pre->Next = node;
	next->Previous = node;
	this->count++;
	return LinkedListIterator(node);

}

template<typename TValue>
typename LinkedList<TValue>::LinkedListIterator LinkedList<TValue>::Remove(LinkedListIterator&& it)
{
	LinkedListNode* current = it.pItem;
	LinkedListNode* next = current->Next;
	LinkedListNode* pre = current->Previous;
	pre->Next = current->Next;
	next->Previous = current->Previous;
	delete current;
	this->count--;
	return LinkedListIterator(next);
}

template<typename TValue>
int LinkedList<TValue>::Count()
{
	return this->count;
}

template<typename TValue>
template<typename TComparator>
typename LinkedList<TValue>::LinkedListIterator LinkedList<TValue>::Find(TValue value, TComparator comparator)
{
	for (auto i = this->Begin(); i != this->End(); ++i)
	{
		if (comparator(value, *i))
		{
			return i;
		}
	}
	return this->End();
}

template<typename TValue>
typename LinkedList<TValue>::LinkedListIterator& LinkedList<TValue>::LinkedListIterator::operator++() noexcept
{
	this->pItem = this->pItem->Next;
	return *this;
}

template<typename TValue>
typename LinkedList<TValue>::LinkedListIterator& LinkedList<TValue>::LinkedListIterator::operator--() noexcept
{
	this->pItem = this->pItem->Previous;
	return *this;
}

template<typename TValue>
bool LinkedList<TValue>::LinkedListIterator::operator==(const LinkedListIterator& other) const noexcept
{
	return this->pItem == other.pItem;
}

template<typename TValue>
bool LinkedList<TValue>::LinkedListIterator::operator!=(const LinkedListIterator& other) const noexcept
{
	return this->pItem != other.pItem;
}

template<typename TValue>
TValue& LinkedList<TValue>::LinkedListIterator::operator*()
{
	return this->pItem->Value;
}

template<typename TValue>
TValue* LinkedList<TValue>::LinkedListIterator::operator->()
{
	return &this->pItem->Value;
}

template<typename TValue>
LinkedList<TValue>::LinkedListIterator::operator ReversedLinkedListIterator()
{
	ReversedLinkedListIterator rIt(*this);
	return rIt;
}

template<typename TValue>
LinkedList<TValue>::LinkedListIterator::LinkedListIterator(ReversedLinkedListIterator& rIt)
{
	this->pItem = rIt.pItem;
}

template<typename TValue>
LinkedList<TValue>::LinkedListIterator::LinkedListIterator(LinkedListNode* pItem)
{
	this->pItem = pItem;
}


template<typename TValue>
typename LinkedList<TValue>::ReversedLinkedListIterator& LinkedList<TValue>::ReversedLinkedListIterator::operator++() noexcept
{
	this->pItem = this->pItem->Previous;
	return *this;
}

template<typename TValue>
typename LinkedList<TValue>::ReversedLinkedListIterator& LinkedList<TValue>::ReversedLinkedListIterator::operator--() noexcept
{
	this->pItem = this->pItem->Next;
	return *this;
}

template<typename TValue>
bool LinkedList<TValue>::ReversedLinkedListIterator::operator==(const ReversedLinkedListIterator& other) const noexcept
{
	return this->pItem == other.pItem;
}

template<typename TValue>
bool LinkedList<TValue>::ReversedLinkedListIterator::operator!=(const ReversedLinkedListIterator& other) const noexcept
{
	return this->pItem != other.pItem;
}

template<typename TValue>
TValue& LinkedList<TValue>::ReversedLinkedListIterator::operator*()
{
	return this->pItem->Value;
}

template<typename TValue>
TValue* LinkedList<TValue>::ReversedLinkedListIterator::operator->()
{
	return &this->pItem->Value;
}

template<typename TValue>
LinkedList<TValue>::ReversedLinkedListIterator::operator LinkedListIterator()
{
	LinkedListIterator it(*this);
	return it;
}

template<typename TValue>
LinkedList<TValue>::ReversedLinkedListIterator::ReversedLinkedListIterator(LinkedListIterator& it)
{
	this->pItem = it.pItem;
}

template<typename TValue>
LinkedList<TValue>::ReversedLinkedListIterator::ReversedLinkedListIterator(LinkedListNode* pItem)
{
	this->pItem = pItem;
}

bool ExponentComparator::operator()(const PolyItem& left, const PolyItem& right)
{
	return left.Exponent == right.Exponent;
}

bool CoefficientComparator::operator()(const PolyItem& left, const PolyItem& right)
{
	return left.Coefficient == right.Coefficient;
}


PolyString AddTwoPoly(PolyString& p1, PolyString& p2)
{
	PolyString pSum;
	ExponentComparator findSameExp;

	// 时间复杂度约n^2, 空间复杂度常数

	// 遍历p1, 把p2的相同指数一并放到pSum并调整顺序
	for (auto it = p1.Begin(); it != p1.End(); ++it)
	{
		PolyItem item = *it;
		auto pos2 = p2.Find(item, findSameExp);
		int newCoef = item.Coefficient;
		if (pos2 != p2.End())
		{
			newCoef += pos2->Coefficient;
		}
		// 无论系数是否为0, 都插入, 后续再删除
		PolyItem newItem = { newCoef, it->Exponent };
		if (pSum.Count() == 0)
		{
			// 没有元素, 直接放到第一个
			pSum.Insert(newItem, pSum.Begin());
		}
		else
		{
			auto fastIt = pSum.Begin();
			// 指数最小, 放到第一个
			if (newItem.Exponent < fastIt->Exponent)
			{
				pSum.Insert(newItem, std::move(fastIt));
				continue;
			}

			// 比较指数, 放在合适的位置
			auto slowIt = pSum.Begin();
			++fastIt;
			while (fastIt != pSum.End())
			{
				// 不会出现相等的情况
				if (newItem.Exponent > slowIt->Exponent
					&& newItem.Exponent < fastIt->Exponent)
				{
					break;
				}
				++fastIt;
				++slowIt;
			}
			pSum.Insert(newItem, std::move(fastIt));
		}
	}

	// 遍历p2, 把pSum中没有的指数加进去
	for (auto it = p2.Begin(); it != p2.End(); ++it)
	{
		PolyItem item = *it;
		auto posSum = pSum.Find(item, findSameExp);
		// pSum中没有该指数才会插入
		// 与之前类似, 把item放到合适的位置
		if (posSum == pSum.End())
		{
			if (pSum.Count() == 0)
			{
				pSum.Insert(item, pSum.Begin());
			}
			else
			{
				auto fastIt = pSum.Begin();
				if (item.Exponent < fastIt->Exponent)
				{
					pSum.Insert(item, std::move(fastIt));
					continue;
				}

				++fastIt;
				auto slowIt = pSum.Begin();			
				while (fastIt != pSum.End())
				{
					if (item.Exponent > slowIt->Exponent
						&& item.Exponent < fastIt->Exponent)
					{
						break;
					}
					++fastIt;
					++slowIt;
				}
				pSum.Insert(item, std::move(fastIt));
			}
		}
	}

	// 寻找系数为0的项，移除它们
	PolyItem zeroCoef = { 0,0 };
	CoefficientComparator findSameCoef;
	auto item = pSum.Find(zeroCoef, findSameCoef);
	while (item != pSum.End())
	{
		pSum.Remove(std::move(item));
		item = pSum.Find(zeroCoef, findSameCoef);
	}
	
	return pSum;
}


#endif 

