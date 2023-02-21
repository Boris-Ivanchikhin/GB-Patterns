
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