#include "include/Factory.h"

//#include "include/WinterGround.h"
//#include "include/WinterHouse.h"
//#include "include/WinterTank.h"

// * class WinterFactory

Ground* WinterFactory::CreateGround()
{
    return new (nothrow) WinterGround;
}

House* WinterFactory::CreateHouse()
{
    return new (nothrow) WinterHouse;
}

Tank* WinterFactory::CreateTank()
{
    return new (nothrow) WinterTank;
}

void WinterFactory::CreateLevel1 (vector<GameObject*> & refStaticObjVec)
{
    auto& _screen = ScreenSingleton::getInstance();

    const uint16_t maxX = _screen.GetMaxX();
    const uint16_t maxY = _screen.GetMaxY();
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;

    Ground* pGr = CreateGround();
    const uint16_t groundY = maxY - 5;
    pGr->SetPos(offset + 1, groundY);
    pGr->SetWidth(width - 2);
    refStaticObjVec.push_back(pGr);

    Tank* pTank = CreateTank();
    pTank->SetWidth(13);
    pTank->SetPos(30, groundY - 1);
    refStaticObjVec.push_back(pTank);

    pTank = CreateTank();
    pTank->SetWidth(13);
    pTank->SetPos(50, groundY - 1);
    refStaticObjVec.push_back(pTank);

    House* pHouse = CreateHouse();
    pHouse->SetWidth(13);
    pHouse->SetPos(80, groundY - 1);
    refStaticObjVec.push_back(pHouse);
}



