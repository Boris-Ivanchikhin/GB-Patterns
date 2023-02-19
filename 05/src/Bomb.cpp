
#include <iostream>
#include <algorithm>

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

void Bomb::Report(Lesson_05::IEventLogger *logger)
{
    logger->WriteEvent(this);
}

void Bomb::AddObserver(DestroyableGroundObject *observer)
{
    if (find(observers.begin(), observers.end(), observer) != observers.end())
        observers.emplace_back(observer);
}

void Bomb::RemoveObserver(DestroyableGroundObject *observer)
{
    auto it = find(observers.begin(), observers.end(), observer);
    observers.erase(it);
}

optional<DestroyableGroundObject *> Bomb::CheckDestoyableObjects()
{
    const double size = GetWidth();
    const double size_2 = size / 2;

    for (auto& observer : observers)
    {
        const double x1 = GetX() - size_2;
        const double x2 = x1 + size;
        if (observer->HandleInsideCheck (x1, x2))
            // return
            return observer;
    }
    // return
    return nullopt;
}


namespace Lesson_02
{
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
}

