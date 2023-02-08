
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

void House::DrawFigure(MyTools::ScreenSingleton& _screen) const
{
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

void House::Draw() const
{
    auto& _screen = ScreenSingleton::getInstance();
    _screen.SetColor(CC_Yellow);
    DrawFigure(_screen);

    /*
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
    */

}

namespace Lesson_04
{
    void GreenHouse::Draw() const
    {
        auto& _screen = ScreenSingleton::getInstance();
        _screen.SetColor(CC_Green);
        DrawFigure(_screen);
    }

    void RedHouse::Draw() const
    {
        auto& _screen = ScreenSingleton::getInstance();
        _screen.SetColor(CC_Red);
        DrawFigure(_screen);
    }

    void BuildExample ()
    {

        Supervisor boss;
        RedCityBuilder red_builder;
        GreenCityBuilder green_builder;

        City* red_city = boss.CreateCity(red_builder);
        cout << "Red city:" << endl;
        red_city->info();

        City* green_city = boss.CreateCity(green_builder);
        cout << endl << "Green city:" << endl;
        green_city->info();

    }

}
