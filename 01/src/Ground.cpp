#include <iostream>
#include <cstring>

#include "include/MyTools.h"
#include "include/Ground.h"

using namespace std;
using namespace MyTools;

//==================================================================================================

void Crater::Draw() const
{
    if (width == SMALL_CRATER_SIZE) // Рисование воронки в 9 символов шириной
    {
        ScreenSingleton::getInstance().GotoXY(x - 4, y + 1);
        cout << "==     ==";
        ScreenSingleton::getInstance().GotoXY(x - 2, y + 2);
        cout << "=====";
    }
}

bool Crater::isInside(double xn) const
{
    const double size_2 = width / 2.0;
    if (int(xn) > int(x - size_2) && xn <= int(x + size_2))
    {
        return true;
    }

    return false;
}

//==================================================================================================

void Ground::Draw() const
{
    auto& _screen = MyTools::ScreenSingleton::getInstance();
    _screen.SetColor(CC_Green);

    const size_t bufSize = width + 1;
    char* buf = new (nothrow) char[bufSize];
    if (buf == nullptr)
    {
        return;
    }

    if (vecCrates.size() == 0)
    {
        _screen.GotoXY(x, y);
        memset(buf, '=', bufSize);
        buf[bufSize - 1] = '\0';
        cout << buf;
    }
    else
    {
        const size_t X = size_t(x);
        char c;
        for (size_t i = X; i < width + X; i++)
        {
            c = (isInsideAnyCrater((double)i)) ? ' ' : '=';
            buf[i - X] = c;
        }

        _screen.GotoXY((double)X, y);
        buf[bufSize-1] = '\0';
        cout << buf;

        for (size_t i = 0; i < vecCrates.size(); i++)
        {
            vecCrates[i].Draw();
        }
    }

    delete[] buf;
}

bool Ground::isInsideAnyCrater(double x) const
{
    bool isInside = false;
    for (size_t i = 0; i < vecCrates.size(); i++)
    {
        if (vecCrates[i].isInside(x))
        {
            isInside = true;
            break;
        }
    }

    return isInside;
}

void Ground::AddCrater(double xn)
{
    Crater cr;
    cr.SetPos(int(xn), y);
    cr.SetWidth(SMALL_CRATER_SIZE);
    vecCrates.push_back(cr);
}