
#ifndef BOMB_OBSERVER_H
#define BOMB_OBSERVER_H

/* =============================================================================================
 * *** Lesson 05.  Patterns: Facade, Visitor and Observer
 *
 *  2.  ���������� �������� �������������*.
 *      ������� ����� Observable �������� � �������� AddObserver,
 *      � ������� ���� ����������� � ������ ��������, ������� ����� ���������.
 *      � ����������� ����� ������� HandleInsideCheck.
 *      ��� ����������� ����� � ����� ����� ���������� �������:
 *      pBomb->CheckDestoyableObjects();
 *      � ������� � ����� ��� ���� ������������ ���������� �������-������� HandleInsideCheck.
 *      ���� �������� ������� true, �� ���������� ��������� �� ���� DestroyableGroundObject � ����� SBomber ��� �������� �����
 *      �� ����������� ������� � �������� ������� �� ������� ����������� ��������.
 *      ���� �� ���� ������ �� ��� ���������, ����� ������������ nullptr.
 *      �� ���� ���������� ���������� �������:
 *      void SBomber::CheckDestoyableObjects(Bomb * pBomb)
 *      �������� ��� ���������������� � ����� Bomb.
 *
 *      � �����, ����� �������� ��������� �������, ������ ����� ���������� ����������� �������:
 *      void SBomber::CheckBombsAndGround()
 *
 *  P.S.
 *      ����������� ������������ ������: class IObserver, class ISubject.
 *
 *      ��������� ������������ class Bomb : public DynamicObject, public Lesson_05::ISubject.
 *      � ����� Bomb �������� ������ <DestroyableGroundObject*> � ����������� override ������ ���������� ISubject.
 *
 *      ��������� ������������ class DestroyableGroundObject : public GameObject, public Lesson_05::IObserver.
 *
 *      ���������� override ����� bool Tank::HandleInsideCheck(double, double) const override;
 *      ���������� override ����� bool House::HandleInsideCheck(double, double) const override;
 *
 *      �������� ������ class SBomber:
 *      - void SBomber::DropBomb()
 *      - void SBomber::DeleteStaticObj(GameObject* pObj)
 *      - void SBomber::DeleteDynamicObj(DynamicObject* pObj)
 *      - void SBomber::CheckBombsAndGround()
 *
 * ============================================================================================= */

#include <iostream>
#include <optional>

//#include "include/DestroyableGroundObject.h"
class DestroyableGroundObject;

using namespace std;

namespace Lesson_05
{
    class IObserver
    {
    public:
        // update ()
        virtual bool HandleInsideCheck (double, double) const = 0;
    };

    class ISubject
    {
    public:
        virtual void AddObserver (DestroyableGroundObject *) = 0; // registerObserver (IObserver *)
        virtual void RemoveObserver (DestroyableGroundObject *) = 0;
        virtual optional <DestroyableGroundObject*> CheckDestoyableObjects() = 0; // NotifyObservers ()
    };
}

#endif //BOMB_OBSERVER_H
