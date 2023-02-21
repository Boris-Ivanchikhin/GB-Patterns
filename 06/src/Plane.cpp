#include <iostream>

#include "include/Plane.h"

using namespace std;

void Plane::Draw() const
{
    auto& _screen = Lesson_01::ScreenSingleton::getInstance();
    _screen.SetColor(CC_LightBlue);

    DrawBody(_screen);
    DrawTail(_screen);
    DrawWings(_screen);
}

void Plane::DrawBody(Lesson_01::ScreenSingleton& _screen) const
{
    _screen.GotoXY(x, y);
    cout << "=========>";
}

void Plane::DrawTail(Lesson_01::ScreenSingleton& _screen) const
{
    _screen.SetColor(CC_LightBlue);
    _screen.GotoXY(x - 2, y - 1);
    cout << "===";
}

void Plane::DrawWings(Lesson_01::ScreenSingleton& _screen) const
{

    _screen.GotoXY(x + 3, y - 1);
    cout << "\\\\\\\\";
    _screen.GotoXY(x + 3, y + 1);
    cout << "////";
}

namespace Lesson_06
{
    void ColorPlane::Draw() const
    {
        auto &_screen = Lesson_01::ScreenSingleton::getInstance();

        _screen.SetColor(CC_Yellow);
        DrawBody(_screen);

        _screen.SetColor(CC_LightCyan);
        DrawTail(_screen);

        _screen.SetColor(CC_LightRed);
        DrawWings(_screen);
    }

    void BigPlane::DrawBody(Lesson_01::ScreenSingleton &_screen) const
    {
        _screen.GotoXY(x, y);
        cout << "==============>";
    }

    void BigPlane::DrawTail(Lesson_01::ScreenSingleton &_screen) const
    {
        _screen.SetColor(CC_LightBlue);
        _screen.GotoXY(x - 2, y - 1);
        cout << "======";
    }

    void BigPlane::DrawWings(Lesson_01::ScreenSingleton &_screen) const
    {
        _screen.GotoXY(x + 3, y - 1);
        cout << "\\\\\\\\\\\\\\";
        _screen.GotoXY(x + 3, y + 1);
        cout << "////////";
    }
}