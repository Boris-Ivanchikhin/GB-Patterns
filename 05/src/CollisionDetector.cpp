#include "include/SBomber.h"
#include "include/CollisionDetector.h"

namespace Lesson_04 {

    // * class Collision {

    Plane* Collision::FindPlane() const {
        for (size_t i = 0; i < vecDynamicObj->size(); i++) {
            Plane *p = dynamic_cast<Plane *>((*vecDynamicObj)[i]);
            if (p != nullptr) {
                return p;
            }
        }

        return nullptr;
    }

    Ground* Collision::FindGround() const
    {
        Ground* pGround;

        for (size_t i = 0; i < vecStaticObj->size(); i++)
        {
            pGround = dynamic_cast<Ground *>((*vecStaticObj)[i]);
            if (pGround != nullptr)
            {
                return pGround;
            }
        }

        return nullptr;
    }

    AbstractLevelGUI* Collision::FindLevelGUI() const
    {
        for (size_t i = 0; i < vecStaticObj->size(); i++)
        {
            LevelGUI_1* p = dynamic_cast<LevelGUI_1*>((*vecStaticObj)[i]);
            if (p != nullptr)
            {
                return p;
            }
        }

        return nullptr;
    }

    vector<Bomb*> Collision::FindAllBombs()
    {
        vector<Bomb*> vecBombs;

        for (size_t i = 0; i < vecDynamicObj->size(); i++)
        {
            Bomb* pBomb = dynamic_cast<Bomb*>((*vecDynamicObj)[i]);
            if (pBomb != nullptr)
            {
                vecBombs.push_back(pBomb);
            }
        }

        return vecBombs;
    }

    void Collision::DeleteDynamicObj(DynamicObject* pObj)
    {
        auto it = vecDynamicObj->begin();
        for (; it != vecDynamicObj->end(); it++)
        {
            if (*it == pObj)
            {
                vecDynamicObj->erase(it);
                break;
            }
        }

    }

    void Collision::DeleteStaticObj(GameObject* pObj)
    {
        auto it = vecStaticObj->begin();
        for (; it != vecStaticObj->end(); it++)
        {
            if (*it == pObj)
            {
                vecStaticObj->erase(it);
                break;
            }
        }

    }

    vector <DestroyableGroundObject *> Collision::FindDestoyableGroundObjects() const
    {
        vector<DestroyableGroundObject*> vec;
        Tank* pTank;
        House* pHouse;
        for (size_t i = 0; i < vecStaticObj->size(); i++)
        {
            pTank = dynamic_cast<Tank*>((*vecStaticObj)[i]);
            if (pTank != nullptr)
            {
                vec.push_back(pTank);
                continue;
            }

            pHouse = dynamic_cast<House*>((*vecStaticObj)[i]);
            if (pHouse != nullptr)
            {
                vec.push_back(pHouse);
                continue;
            }
        }

        return vec;
    }


    // * class CollisionDetector

    void CollisionDetector::CheckPlaneAndLevelGUI() {
        if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX()) {
            sBomber->SetExitFlag(true);
        }
    }

    void CollisionDetector::CheckBombsAndGround()
    {
        vector<Bomb*> vecBombs = FindAllBombs();
        Ground* pGround = FindGround();
        const double y = pGround->GetY();
        for (size_t i = 0; i < vecBombs.size(); i++)
        {
            if (vecBombs[i]->GetY() >= y) // The intersection of the bomb with the ground
            {
                pGround->AddCrater(vecBombs[i]->GetX());
                CheckDestoyableObjects(vecBombs[i]);
                DeleteDynamicObj(vecBombs[i]);
            }
        }

    }

    void CollisionDetector::CheckDestoyableObjects(Bomb * pBomb)
    {
        vector<DestroyableGroundObject*> vecDestoyableObjects = FindDestoyableGroundObjects();
        const double size = pBomb->GetWidth();
        const double size_2 = size / 2;
        for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
        {
            const double x1 = pBomb->GetX() - size_2;
            const double x2 = x1 + size;
            if (vecDestoyableObjects[i]->isInside(x1, x2))
            {
                // score += vecDestoyableObjects[i]->GetScore();
                sBomber->SetScore(sBomber->GetScore() + vecDestoyableObjects[i]->GetScore());
                DeleteStaticObj(vecDestoyableObjects[i]);
            }
        }
    }

}

