
#include <iostream>

#include "include/Bomb.h"
#include "include/MyTools.h"

using namespace std;
using namespace MyTools;

void Bomb::Draw() const
{
    Lesson_01::ScreenSingleton::getInstance().SetColor(CC_LightMagenta);
    Lesson_01::ScreenSingleton::getInstance().GotoXY(x, y);
    cout << "*";
}

Bomb::Bomb(const Bomb& _bomb)
{
    // from DynamicObject
    speed = _bomb.speed;
    xDirction = _bomb.xDirction;
    yDirection = _bomb.yDirection;

    // from GameObject
    uint16_t MaxX = Lesson_01::ScreenSingleton::getInstance().GetMaxX();
    x = _bomb.x + 10 < MaxX ? _bomb.x + 10 : _bomb.x + 10 - MaxX;
    y = _bomb.y;
    width = _bomb.width;
}