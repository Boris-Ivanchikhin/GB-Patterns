
#include "include/SBomber.h"

using namespace std;

/* =============================================================================================
 // *** Lesson  07. Patterns: Memento, RAII and PIMPL
 *
 * 2(*). Применить паттерн PIMPL для класса SBomber.
 *      Задача: предположим, что мы хотим распространять класс SBomber как движок — через статические библиотеки (lib).
 *      С ним нам также придётся распространять и заголовочный файл. При нынешней реализации класса его пользователи
 *      увидят его внутренности — переменные и массивы объектов — и, частично, его реализацию (список приватных функций).
 *      Давайте применим шаблон PIMPL, чтобы скрыть приватные функции и члены данных.
 *      Для этого перенесём их в отдельный класс SBomberImpl, а указатель на него объявим в приватной секции класса SBomber.
 *      Члены данных класса SBomberImpl можно сделать публичными, что к ним проще было обращаться из класса SBomber.
 *
 *  P.S.
 *      Создан class SBomber::SBomberImpl.
 *      Внесены изменения в class SBomber.
 *
 * ============================================================================================= */

// class SBomber::SBomberImpl

class SBomber::SBomberImpl
{
public:

    vector<DynamicObject*> vecDynamicObj;
    vector<GameObject*> vecStaticObj;

    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;

public:
    SBomberImpl();
    ~SBomberImpl();

    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void __fastcall CheckDestoyableObjects(Bomb* pBomb);

    void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
    void __fastcall DeleteStaticObj(GameObject* pObj);

    Ground * FindGround() const;
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;

    vector<Bomb*> FindAllBombs() const;

    void DropBomb();

};

// class SBomber::SBomberImpl

SBomber::SBomberImpl::SBomberImpl()
        :   exitFlag(false),
            startTime(0),
            finishTime(0),
            deltaTime(0),
            passedTime(0),
            fps(0),
            bombsNumber(10),
            score(0)
{

}

SBomber::SBomberImpl::~SBomberImpl()
{
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
        if (vecDynamicObj[i] != nullptr)
            delete vecDynamicObj[i];

    for (size_t i = 0; i < vecStaticObj.size(); i++)
        if (vecStaticObj[i] != nullptr)
            delete vecStaticObj[i];
}


void SBomber::SBomberImpl::CheckPlaneAndLevelGUI()
{
    if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX())
        exitFlag = true;
}

void SBomber::SBomberImpl::CheckBombsAndGround()
{
    vector<Bomb*> vecBombs = FindAllBombs();
    Ground* pGround = FindGround();
    const double y = pGround->GetY();
    for (size_t i = 0; i < vecBombs.size(); i++)
    {
        if (vecBombs[i]->GetY() >= y) // ����������� ����� � ������
        {
            pGround->AddCrater(vecBombs[i]->GetX());
            CheckDestoyableObjects(vecBombs[i]);
            DeleteDynamicObj(vecBombs[i]);
        }
    }

}

void SBomber::SBomberImpl::CheckDestoyableObjects(Bomb * pBomb)
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
            score += vecDestoyableObjects[i]->GetScore();
            DeleteStaticObj(vecDestoyableObjects[i]);
        }
    }
}

void SBomber::SBomberImpl::DeleteDynamicObj(DynamicObject* pObj)
{
    auto it = vecDynamicObj.begin();
    for (; it != vecDynamicObj.end(); it++)
    {
        if (*it == pObj)
        {
            vecDynamicObj.erase(it);
            break;
        }
    }
}

void SBomber::SBomberImpl::DeleteStaticObj(GameObject* pObj)
{
    auto it = vecStaticObj.begin();
    for (; it != vecStaticObj.end(); it++)
    {
        if (*it == pObj)
        {
            vecStaticObj.erase(it);
            break;
        }
    }
}

Ground* SBomber::SBomberImpl::FindGround() const
{
    Ground* pGround;

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        pGround = dynamic_cast<Ground *>(vecStaticObj[i]);
        if (pGround != nullptr)
        {
            return pGround;
        }
    }

    return nullptr;
}

Plane* SBomber::SBomberImpl::FindPlane() const
{
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

LevelGUI* SBomber::SBomberImpl::FindLevelGUI() const
{
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        LevelGUI* p = dynamic_cast<LevelGUI*>(vecStaticObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

vector<DestroyableGroundObject*> SBomber::SBomberImpl::FindDestoyableGroundObjects() const
{
    vector<DestroyableGroundObject*> vec;
    Tank* pTank;
    House* pHouse;
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        pTank = dynamic_cast<Tank*>(vecStaticObj[i]);
        if (pTank != nullptr)
        {
            vec.push_back(pTank);
            continue;
        }

        pHouse = dynamic_cast<House*>(vecStaticObj[i]);
        if (pHouse != nullptr)
        {
            vec.push_back(pHouse);
            continue;
        }
    }

    return vec;
}

vector<Bomb*> SBomber::SBomberImpl::FindAllBombs() const
{
    vector<Bomb*> vecBombs;

    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        Bomb* pBomb = dynamic_cast<Bomb*>(vecDynamicObj[i]);
        if (pBomb != nullptr)
        {
            vecBombs.push_back(pBomb);
        }
    }

    return vecBombs;
}

void SBomber::SBomberImpl::DropBomb()
{
    if (bombsNumber > 0)
    {
        Lesson_07::logger.WriteToLog(string(__FUNCTION__) + " was invoked");

        Plane* pPlane = FindPlane();
        double x = pPlane->GetX() + 4;
        double y = pPlane->GetY() + 2;

        Bomb* pBomb = new Bomb;
        pBomb->SetDirection(0.3, 1);
        pBomb->SetSpeed(2);
        pBomb->SetPos(x, y);
        pBomb->SetWidth(SMALL_CRATER_SIZE);

        vecDynamicObj.push_back(pBomb);
        bombsNumber--;
        score -= Bomb::BombCost;
    }
}