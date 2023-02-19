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
#include "include/Tree.h"
#include "include/CollisionDetector.h"

class SBomber
{
public:

    SBomber();
    ~SBomber();
    
    inline bool GetExitFlag() const { return exitFlag; }
    void SetExitFlag(bool exitFlag) { exitFlag = exitFlag; }

    void setExitFlag(bool exitFlag);

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

    int16_t GetScore() const { return score; };

    void SetScore(int16_t score) { score = score; };

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

    ITreeCreator * pTreeCreator;
    void SwitchTree ();

    Lesson_04::CollisionDetector *pCollDetector;
};