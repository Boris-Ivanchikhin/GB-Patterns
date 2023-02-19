
#ifndef COLLISION_H
#define COLLISION_H

#include <iostream>
#include <vector>

#include "include/DynamicObject.h"
#include "include/Bomb.h"
#include "include/Plane.h"
#include "include/Ground.h"
#include "include/DestroyableGroundObject.h"
#include "include/LevelGUI.h"

using namespace std;

class SBomber;
//class GameObject;
//class DynamicObject;
//class Ground;
//class Bomb;
//class Plane;
//class AbstractLevelGUI;
//class DestroyableGroundObject;

/* =============================================================================================
 * *** Lesson 04.  Patterns: Factory Method, Builder, Bridge
 *
 *  2.(*) Применяем паттерн «Мост»*
 *      Разгрузить класс SBomber. С помощью шаблона «Мост» вынести в отдельный объект функциональность,
 *      связанную с проверкой столкновений в игре.
 *
 * ============================================================================================= */

namespace Lesson_04 {

    class Collision {
    protected:
        SBomber *sBomber;

        void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
        void __fastcall DeleteStaticObj(GameObject* pObj);

    private:
        vector<DynamicObject *> *vecDynamicObj;
        vector<GameObject *> *vecStaticObj;

    public:
        Collision(SBomber *_sBomber, vector<DynamicObject *> *_VDynamic, vector<GameObject *> *_VStatic)
        : sBomber (_sBomber), vecDynamicObj (_VDynamic), vecStaticObj (_VStatic)
        {};

        Ground *FindGround() const;
        Plane *FindPlane() const;
        AbstractLevelGUI * FindLevelGUI() const;
        vector <Bomb*> FindAllBombs();
        vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;

    };

    class CollisionDetector : public Collision {
    public:
        CollisionDetector (SBomber *_sBomber, vector<DynamicObject *> *_VDynamic, vector<GameObject *> *_VStatic)
        : Collision (_sBomber, _VDynamic, _VStatic)
        {};

        void CheckPlaneAndLevelGUI();

        void CheckBombsAndGround();

        void __fastcall CheckDestoyableObjects(Bomb *pBomb);

    };
}


#endif //COLLISION_H
