
#include <iostream>

#include "include/Bomb.h"
#include "include/MyTools.h"

using namespace std;
using namespace MyTools;

void Bomb::Draw() const
{
    ScreenSingleton::getInstance().SetColor(CC_LightMagenta);
    ScreenSingleton::getInstance().GotoXY(x, y);
    cout << "*";
}

void BombDecorator::Move(uint16_t time)
{
    bomb->Move(time * 1.5);
}

void BombDecorator::Draw() const
{
    bomb->Draw();

    ScreenSingleton::getInstance().GotoXY(bomb->GetX(), bomb->GetY() - 1);
    cout << "0";
}
