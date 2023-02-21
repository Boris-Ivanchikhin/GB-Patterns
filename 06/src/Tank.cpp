
#include <random>

#include "include/Tank.h"
#include "include/MyTools.h"

using namespace std;
using namespace MyTools;

TankMediator* Tank::mediator = nullptr;

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

    if (Elapsed() > Timeout)
    {
		string msg{};
		// distribution int of RNG
		uniform_int_distribution <int> RNG_INT(0, 20);
		// create & initialize RNG
		mt19937 gen {random_device()()};
		// choice phrase
		if ( RNG_INT(gen) >= 10)
			msg = "we are the champions!";
		else
			msg = "mammy!!!";
		// notify
		if (mediator)
		{
			mediator->Notify(msg);
			start = clock_t::now();
		}

    }
}


