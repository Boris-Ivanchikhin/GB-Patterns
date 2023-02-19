
#include <iostream>

#include "include/Plane.h"
#include "include/MyTools.h"

using namespace std;
using namespace MyTools;

void Plane::Draw() const
{
    auto& _screen = ScreenSingleton::getInstance();
    _screen.SetColor(CC_LightBlue);
    _screen.GotoXY(x, y);
    cout << "=========>";
    _screen.GotoXY(x - 2, y - 1);
    cout << "===";
    _screen.GotoXY(x + 3, y - 1);
    cout << "\\\\\\\\";
    _screen.GotoXY(x + 3, y + 1);
    cout << "////";
}

void Plane::Report(Lesson_05::IEventLogger *logger)
{
    logger->WriteEvent(this);
}
