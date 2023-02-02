#ifndef FACTORY_H
#define FACTORY_H

#include <vector>

#include "include/GameObject.h"
#include "include/Ground.h"
#include "include/House.h"
#include "include/Tank.h"
#include "include/MyTools.h"

using namespace std;
using namespace MyTools;

class WinterGround : public Ground
{
public:
    WinterGround() = default;
    ~WinterGround() = default;

    void Draw() const override
    {
        ScreenSingleton::getInstance().SetColor(CC_Blue);
        Ground::Draw();
    };
};

class WinterTank : public Tank
{
public:
    WinterTank() = default;
    ~WinterTank() = default;

    void Draw() const override
    {
        ScreenSingleton::getInstance().SetColor(CC_Blue);
        Tank::Draw();
    };
};

class WinterHouse : public House
{
public:
    WinterHouse () = default;
    ~WinterHouse () = default;

    void Draw() const override
    {
        ScreenSingleton::getInstance().SetColor(CC_Blue);
        House::Draw();
    };
};

class AbstractFactory
{
public:
    AbstractFactory () = default;
    virtual ~AbstractFactory() = default;

    virtual Ground* CreateGround() = 0;
    virtual House* CreateHouse() = 0;
    virtual Tank* CreateTank() = 0;
    virtual void CreateLevel1(std::vector<GameObject*>& refStaticObjVec) = 0;
};

class WinterFactory : public AbstractFactory
{
public:
    Ground* CreateGround() override;
    House* CreateHouse() override;
    Tank* CreateTank() override;
    void CreateLevel1(std::vector<GameObject*>& refStaticObjVec) override;
};

#endif // FACTORY_H