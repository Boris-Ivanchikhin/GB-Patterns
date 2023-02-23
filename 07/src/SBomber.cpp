
#include <conio.h>
#include <windows.h>

#include "include/SBomber.h"
#include "include/Bomb.h"
#include "include/Ground.h"
#include "include/Tank.h"
#include "include/House.h"
#include "include/MyTools.h"
#include "include/FileLogger.h"

#include "SBomberImpl.cpp"

using namespace std;
using namespace MyTools;

// class SBomber

SBomber::SBomber()
:   pImpl(new SBomberImpl())

{

    Lesson_07::logger.WriteToLog(string{__FUNCTION__} + " was invoked");

    Plane* p = new Plane;
    p->SetDirection(1, 0.1);
    p->SetSpeed(4);
    p->SetPos(5, 10);
    pImpl->vecDynamicObj.push_back(p);

    LevelGUI* pGUI = new LevelGUI;
    pGUI->SetParam(pImpl->passedTime, pImpl->fps,
                                pImpl->bombsNumber, pImpl->score);
    const uint16_t maxX = GetMaxX();
    const uint16_t maxY = GetMaxY(); 
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;
    pGUI->SetPos(offset, offset);
    pGUI->SetWidth(width);
    pGUI->SetHeight(maxY - 4);
    pGUI->SetFinishX(offset + width - 4);
    pImpl->vecStaticObj.push_back(pGUI);

    Ground* pGr = new Ground;
    const uint16_t groundY = maxY - 5;
    pGr->SetPos(offset + 1, groundY);
    pGr->SetWidth(width - 2);
    pImpl->vecStaticObj.push_back(pGr);

    Tank* pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(30, groundY - 1);
    pImpl->vecStaticObj.push_back(pTank);

    pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(50, groundY - 1);
    pImpl->vecStaticObj.push_back(pTank);

    House * pHouse = new House;
    pHouse->SetWidth(13);
    pHouse->SetPos(80, groundY - 1);
    pImpl->vecStaticObj.push_back(pHouse);

    /*
    Bomb* pBomb = new Bomb;
    pBomb->SetDirection(0.3, 1);
    pBomb->SetSpeed(2);
    pBomb->SetPos(51, 5);
    pBomb->SetSize(SMALL_CRATER_SIZE);
    vecDynamicObj.push_back(pBomb);
    */
}

SBomber::~SBomber()
{
    /*
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        if (vecDynamicObj[i] != nullptr)
        {
            delete vecDynamicObj[i];
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        if (vecStaticObj[i] != nullptr)
        {
            delete vecStaticObj[i];
        }
    }
    */

    delete pImpl;
}

bool SBomber::GetExitFlag() const
{
    return pImpl->exitFlag;
}

void SBomber::MoveObjects()
{
    Lesson_07::logger.WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < pImpl->vecDynamicObj.size(); i++)
    {
        if (pImpl->vecDynamicObj[i] != nullptr)
        {
            pImpl->vecDynamicObj[i]->Move(pImpl->deltaTime);
        }
    }
};

void SBomber::CheckObjects()
{
    Lesson_07::logger.WriteToLog(string(__FUNCTION__) + " was invoked");

    pImpl->CheckPlaneAndLevelGUI();
    pImpl->CheckBombsAndGround();
};

void SBomber::ProcessKBHit()
{
    int c = _getch();

    if (c == 224)
    {
        c = _getch();
    }

    Lesson_07::logger.WriteToLog(string(__FUNCTION__) + " was invoked. key = ", c);

    switch (c) {

    case 27: // esc
        pImpl->exitFlag = true;
        break;

    case 72: // up
        pImpl->FindPlane()->ChangePlaneY(-0.25);
        break;

    case 80: // down
        pImpl->FindPlane()->ChangePlaneY(0.25);
        break;

    case 'b':
        pImpl->DropBomb();
        break;

    case 'B':
        pImpl->DropBomb();
        break;

    default:
        break;
    }
}

void SBomber::DrawFrame()
{
    Lesson_07::logger.WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < pImpl->vecDynamicObj.size(); i++)
    {
        if (pImpl->vecDynamicObj[i] != nullptr)
        {
            pImpl->vecDynamicObj[i]->Draw();
        }
    }

    for (size_t i = 0; i < pImpl->vecStaticObj.size(); i++)
    {
        if (pImpl->vecStaticObj[i] != nullptr)
        {
            pImpl->vecStaticObj[i]->Draw();
        }
    }

    GotoXY(0, 0);
    pImpl->fps++;

    pImpl->FindLevelGUI()->SetParam(pImpl->passedTime, pImpl->fps,
                                    pImpl->bombsNumber, pImpl->score);
}

void SBomber::TimeStart()
{
    Lesson_07::logger.WriteToLog(string(__FUNCTION__) + " was invoked");
    pImpl->startTime = GetTickCount64();
}

void SBomber::TimeFinish()
{
    pImpl->finishTime = GetTickCount64();
    pImpl->deltaTime = uint16_t(pImpl->finishTime - pImpl->startTime);
    pImpl->passedTime += pImpl->deltaTime;

    Lesson_07::logger.WriteToLog(string(__FUNCTION__) + " deltaTime = ", (int)pImpl->deltaTime);
}
