#include "include/Commands.h"
#include "include/MyTools.h"
#include "include/Bomb.h"
#include "include/Ground.h"

using namespace MyTools;

namespace Lesson_02
{
    void CommandDropBomb::Execute()
    {

        LoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

        double x = pPlane->GetX() + 4;
        double y = pPlane->GetY() + 2;

        Bomb* pBomb = new Bomb;
        pBomb->SetDirection(0.3, 1);
        pBomb->SetSpeed(2);
        pBomb->SetPos(x, y);
        pBomb->SetWidth(SMALL_CRATER_SIZE);

        vecObj->push_back(pBomb);

    }
}
