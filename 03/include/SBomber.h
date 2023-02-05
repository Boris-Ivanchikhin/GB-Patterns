#pragma once

#include <vector>

#include "include/LevelGUI.h"
#include "include/Plane.h"
#include "include/Bomb.h"
#include "include/Ground.h"
#include "include/Tank.h"
#include "include/Factory.h"
#include "include/Commands.h"
#include "include/BombIterator.h"

class SBomber
{
public:

    SBomber();
    ~SBomber();
    
    inline bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

private:

    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void __fastcall CheckDestoyableObjects(Bomb* pBomb);

    void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
    void __fastcall DeleteStaticObj(GameObject* pObj);
    void __fastcall CommandExecuter(auto * pCommand);


    Ground * FindGround() const;
    Plane * FindPlane() const;
    AbstractLevelGUI * FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    std::vector<Bomb*> FindAllBombs();

    void DropBomb();

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;

    // an iterator that is configured to start a vector
    BombIterator begin ()
    {
        BombIterator it(vecDynamicObj);
        return it;
    };

    // an iterator that is configured to end a vector
    BombIterator end()
    {
        BombIterator it(vecDynamicObj);
        it.reset();
        return it;
    };

    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;

    AbstractFactory* pFactory;
};