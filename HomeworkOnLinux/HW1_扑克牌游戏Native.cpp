// 1853760 贺兰山

// 迫不得已写一份不用算法库的

#include <iostream>
#include <string>
#include <string.h>


// #define ACTIVE
#ifdef ACTIVE
#define MAIN int main()
#else
#define MAIN static int test()
#endif

using CardColor = int;
using CardPoint = int;

constexpr CardColor Club = 1;
constexpr CardColor Spade = 2;
constexpr CardColor Heart = 3;
constexpr CardColor Diamond = 4;

using Card = int;

Card StringToCard(std::string& colorStr, std::string& pointStr);
std::string CardToString(Card card);
inline CardColor StringToColor(std::string& colorStr);
inline CardPoint StringToPoint(std::string& pointStr);
inline std::string ColorToString(CardColor color);
inline std::string PointToString(CardPoint point);
inline CardColor ColorOf(Card card);
inline CardPoint PointOf(Card card);
inline Card CardOf(CardColor color, CardPoint point);

constexpr int maxSize = 256;
Card cards[maxSize] = {0};
int beginIndex = 0;
int endIndex = 1;
bool isReversed = false;

inline bool IsCardsEmpty();
inline int HeadIndex();
inline int TailIndex();
inline int Length();
inline Card Pop(); //unchecked
inline void Append(Card card);
inline void Reverse();
inline void Extract(CardColor color);


MAIN
{
	//freopen("input10.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	int cmdCount;
	std::cin >> cmdCount;
	for (int i = 0; i < cmdCount; i++)
	{
		std::string cmd;
		std::cin >> cmd;
		if (cmd == "Pop")
		{
			if (IsCardsEmpty())
			{
				std::cout << "NULL\n";
			}
			else
			{
				Card card =	Pop();
				std::cout << CardToString(card) << std::endl;
			}
		}
		else if (cmd == "Append")
		{
			std::string colorStr, pointStr;
			std::cin >> colorStr >> pointStr;
			Card card = StringToCard(colorStr, pointStr);
			Append(card);
		}
		else if (cmd == "Revert")
		{
			Reverse();
		}
		else if (cmd == "Extract")
		{
			std::string colorStr;
			std::cin >> colorStr;
			CardColor color = StringToColor(colorStr);
			Extract(color);
		}

	}

	if (isReversed)
	{
		for (int i = beginIndex + 1; i < endIndex; i++)
		{
			std::cout << CardToString(cards[i]) << std::endl;
		}
	}
	else
	{
		for (int i = endIndex - 1; i > beginIndex; i--)
		{
			std::cout << CardToString(cards[i]) << std::endl;
		}
	}
}

Card StringToCard(std::string& colorStr, std::string& pointStr)
{
	CardColor color = StringToColor(colorStr);
	CardPoint point = StringToPoint(pointStr);
	return color * 100 + point;
}

std::string CardToString(Card card)
{
	std::string str = ColorToString(ColorOf(card));
	str += " ";
	str += PointToString(PointOf(card));
	return str;
}

inline CardColor StringToColor(std::string& colorStr)
{
	CardColor color = 0;
	if (colorStr == "Club")
	{
		color = Club;
	}
	else if (colorStr == "Spade")
	{
		color = Spade;
	}
	else if (colorStr == "Heart")
	{
		color = Heart;
	}
	else if (colorStr == "Diamond")
	{
		color = Diamond;
	}
	return color;
}

inline CardPoint StringToPoint(std::string& pointStr)
{
	CardPoint point = 0;
	if (pointStr == "A")
	{
		point = 1;
	}
	else if (pointStr == "J")
	{
		point = 11;
	}
	else if (pointStr == "Q")
	{
		point = 12;
	}
	else if (pointStr == "K")
	{
		point = 13;
	}
	else
	{
		point = std::stoi(pointStr);
	}
	return point;
}

inline std::string ColorToString(CardColor color)
{
	std::string str;
	switch (color)
	{
	case Spade:
		str = "Spade";
		break;
	case Club:
		str = "Club";
		break;
	case Heart:
		str = "Heart";
		break;
	case Diamond:
		str = "Diamond";
		break;
	default:
		break;
	}
	return str;
}

inline std::string PointToString(CardPoint point)
{
	std::string str;
	switch (point)
	{
	case 1:
		str = "A";
		break;
	case 11:
		str = "J";
		break;
	case 12:
		str = "Q";
		break;
	case 13:
		str = "K";
		break;
	default:
		str = std::to_string(point);
		break;
	}
	return str;
}

inline CardColor ColorOf(Card card)
{
	return card / 100;
}

inline CardPoint PointOf(Card card)
{
	return card % 100;
}

inline Card CardOf(CardColor color, CardPoint point)
{
	return color * 100 + point;
}

inline bool IsCardsEmpty()
{
	return endIndex == beginIndex + 1;
}

inline int HeadIndex()
{
	if (!isReversed)
	{
		return endIndex;
	}
	else
	{
		return beginIndex;
	}
}

inline int TailIndex()
{
	if (isReversed)
	{
		return endIndex;
	}
	else
	{
		return beginIndex;
	}
}

inline int Length()
{
	return endIndex - beginIndex - 1;
}

inline Card Pop()
{
	int head = HeadIndex();
	if (!isReversed)
	{
		head--;
		endIndex = head;
	}
	else
	{
		head++;
		beginIndex = head;
	}
	Card card = cards[head];
	cards[head] = 0;
	return card;
}

inline void Append(Card card)
{
	int tail = TailIndex();
	if (isReversed)
	{
		if (tail == maxSize - 1)
		{
			int len = Length();
			memmove(cards + 5, cards + beginIndex + 1, len * sizeof(Card));
			beginIndex = 4;
			endIndex = beginIndex + len + 1;
			tail = endIndex;
		}
		cards[tail] = card;
		tail++;
		endIndex = tail;
	}
	else
	{
		if (tail == 0)
		{
			int len = Length();
			memmove(cards + 5, cards + beginIndex + 1, len * sizeof(Card));
			beginIndex = 4;
			endIndex = beginIndex + len + 1;
			tail = beginIndex;
		}
		cards[tail] = card;
		tail--;
		beginIndex = tail;
	}
}

inline void Reverse()
{
	isReversed = !isReversed;
}

int cmpfunc(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

inline void Extract(CardColor color)
{
	Card extracted[maxSize] = { 0 };
	Card reserved[maxSize] = { 0 };
	int totalCount = Length();
	int extractedCount = 0;
	int reservedCount = 0;
	for (int i = beginIndex + 1; i < endIndex; i++)
	{
		if (ColorOf(cards[i]) == color)
		{
			extracted[extractedCount] = cards[i];
			extractedCount++;
		}
		else
		{
			reserved[reservedCount] = cards[i];
			reservedCount++;
		}
	}
	memset(cards, 0, sizeof(Card[maxSize]));
	qsort(extracted, extractedCount, sizeof(Card), cmpfunc);
	if (isReversed)
	{
		for (int i = 0; i < extractedCount; i++)
		{
			cards[i + 1] = extracted[i];
		}
		memcpy(cards + 1 + extractedCount, reserved, sizeof(Card) * reservedCount);
		beginIndex = 0;
		endIndex = beginIndex + totalCount + 1;
	}
	else
	{
		memcpy(cards + 1, reserved, sizeof(Card) * reservedCount);
		for (int i = 0; i < extractedCount; i++)
		{
			cards[1 + reservedCount + i] = extracted[extractedCount - i - 1];
		}
		beginIndex = 0;
		endIndex = beginIndex + totalCount + 1;
	}
}
