
#include <iostream>

#include "include/Tank.h"
#include "include/MyTools.h"

using namespace std;
using namespace MyTools;

bool Tank::isInside(double x1, double x2) const
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

void Tank::Draw() const
{
    auto& _screen = MyTools::Lesson_01::ScreenSingleton::getInstance();
	_screen.SetColor(CC_Brown);
    _screen.GotoXY(x, y - 3);
	cout << "    #####";
    _screen.GotoXY(x-2, y - 2);
	cout << "#######   #";
    _screen.GotoXY(x, y - 1);
	cout << "    #####";
    _screen.GotoXY(x,y);
	cout << " ###########";
}