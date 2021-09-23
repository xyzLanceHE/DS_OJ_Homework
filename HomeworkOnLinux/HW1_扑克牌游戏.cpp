// 1853760 贺兰山

// 这份代码放到OJ上会Runtime Error
// 本地跑得挺好的, 估计OJ会ban库?

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>


//#define ACTIVE
#ifdef ACTIVE
#define MAIN int main()
#else
#define MAIN static int test()
#endif

using std::operator""s;

class PokerCard
{
public:
	enum class Color { Spade, Heart, Club, Diamond };
	int point;
	Color color;
	PokerCard(int point, Color color);
	PokerCard(std::string& valStr);
	std::string ToString();
};

using StringColorPair = std::map<std::string, PokerCard::Color>::value_type;
using StringPointPair = std::map<std::string, int>::value_type;

const StringColorPair ColorMapValue[] =
{
	StringColorPair("Spade"s, PokerCard::Color::Spade),
	StringColorPair("Heart"s, PokerCard::Color::Heart),
	StringColorPair("Diamond"s, PokerCard::Color::Diamond),
	StringColorPair("Club"s, PokerCard::Color::Club),
};

const StringPointPair PointMapValue[] =
{
	StringPointPair("A"s, 1),
	StringPointPair("2"s, 2),
	StringPointPair("3"s, 3),
	StringPointPair("4"s, 4),
	StringPointPair("5"s, 5),
	StringPointPair("6"s, 6),
	StringPointPair("7"s, 7),
	StringPointPair("8"s, 8),
	StringPointPair("9"s, 9),
	StringPointPair("10"s, 10),
	StringPointPair("J"s, 11),
	StringPointPair("Q"s, 12),
	StringPointPair("K"s, 13)
};


const std::map<std::string, PokerCard::Color> ColorMap(ColorMapValue, ColorMapValue + 4);
const std::map<std::string, int> PointMap(PointMapValue, PointMapValue + 13);

class ColorTargetedComparator
{
public:
	ColorTargetedComparator(PokerCard::Color targetColor);
	bool operator()(const PokerCard& left, const PokerCard& right);
private:
	PokerCard::Color color;
};


MAIN
{
	int n;
	std::cin >> n;
	std::vector<PokerCard> cardCollection;
	for (int i = 0; i < n; i++)
	{
		std::string cmd;
		std::cin >> cmd;
		if (cmd == "Pop")
		{
			if (cardCollection.size() == 0)
			{
				std::cout << "NULL\n";
			}
			else
			{
				PokerCard card = *cardCollection.rbegin();			
				cardCollection.pop_back();
				std::cout << card.ToString() << std::endl;
			}
		}
		else if (cmd == "Append")
		{
			std::string cardStr;
			std::getline(std::cin, cardStr);
			PokerCard card(cardStr);
			cardCollection.insert(cardCollection.begin(), card);
		}
		else if (cmd == "Revert")
		{
			std::reverse(cardCollection.begin(), cardCollection.end());
		}
		else if (cmd == "Extract")
		{
			std::string colorStr;
			std::cin >> colorStr;
			try
			{
				PokerCard::Color color = ColorMap.at(colorStr);
				ColorTargetedComparator comparator(color);
				std::stable_sort(cardCollection.begin(), cardCollection.end(), comparator);
			}
			catch (std::out_of_range& e)
			{

			}

		}
	}

	if (cardCollection.size() == 0)
	{
		std::cout << "NULL\n";
	}
	else
	{
		for (auto card = cardCollection.rbegin(); card != cardCollection.rend(); card++)
		{
			std::cout << card->ToString() << std::endl;
		}
	}
	
}

PokerCard::PokerCard(int point, Color color)
{
	this->point = point;
	this->color = color;
}

PokerCard::PokerCard(std::string& valStr)
{
	std::stringstream ss(valStr);
	std::string colorStr, pointStr;
	ss >> colorStr >> pointStr;
	try
	{
		this->color = ColorMap.at(colorStr);
		this->point = PointMap.at(pointStr);
	}
	catch (std::out_of_range&)
	{

	}

}

std::string PokerCard::ToString()
{
	std::string str;
	switch (this->color)
	{
	case PokerCard::Color::Club:
		str = "Club ";
		break;
	case PokerCard::Color::Heart:
		str = "Heart ";
		break;
	case PokerCard::Color::Diamond:
		str = "Diamond ";
		break;
	case PokerCard::Color::Spade:
		str = "Spade ";
		break;
	default:
		break;
	}
	switch (this->point)
	{
	case 1:
		str += "A";
		break;
	case 11:
		str += "J";
		break;
	case 12:
		str += "Q";
		break;
	case 13:
		str += "K";
		break;
	default:
		str += std::to_string(this->point);
		break;
	}
	return str;
}

ColorTargetedComparator::ColorTargetedComparator(PokerCard::Color targetColor)
{
	this->color = targetColor;
}

bool ColorTargetedComparator::operator()(const PokerCard& left, const PokerCard& right)
{
	if (left.color == this->color && right.color == this->color)
	{
		return left.point < right.point;
	}
	else if (left.color == this->color)
	{
		return false;
	}
	else if (right.color == this->color)

	{
		return true;
	}
	else
	{
		return false;
	}
}
