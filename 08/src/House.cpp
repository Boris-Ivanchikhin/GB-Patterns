
#include <iostream>

#include "include/House.h"
#include "include/MyTools.h"

using namespace std;
using namespace MyTools;

bool House::isInside(double x1, double x2) const
{
	const double XBeg = x + 2;
	const double XEnd = x + width - 1;

	if (x1 < XBeg && x2 > XEnd)
	{
		return true;
	}

	if (x1 > XBeg && x1 < XEnd)
	{
		return true;
	}

	if (x2 > XBeg && x2 < XEnd)
	{
		return true;
	}

	return false;
}

void House::Draw() const
{
    auto& _screen = Lesson_01::ScreenSingleton::getInstance();
    _screen.SetColor(CC_Yellow);
    _screen.GotoXY(x, y - 5);
	cout << "  ########  ";
    _screen.GotoXY(x, y - 4);
	cout << "##        ##";
    _screen.GotoXY(x, y - 3);
	cout << "############";
    _screen.GotoXY(x, y - 2);
	cout << "#          #";
    _screen.GotoXY(x, y - 1);
	cout << "#          #";
    _screen.GotoXY(x, y);
	cout << "############";
}