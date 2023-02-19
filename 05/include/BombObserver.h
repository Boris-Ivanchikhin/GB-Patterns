
#ifndef BOMB_OBSERVER_H
#define BOMB_OBSERVER_H

/* =============================================================================================
 * *** Lesson 05.  Patterns: Facade, Visitor and Observer
 *
 *  2.  Применение паттерна «Наблюдатель»*.
 *      Сделать бомбы Observable объектом с функцией AddObserver,
 *      у которой есть наблюдатели — массив объектов, которые можно разрушать.
 *      А наблюдатели имеют функцию HandleInsideCheck.
 *      При пересечении бомбы с землёй будет вызываться функция:
 *      pBomb->CheckDestoyableObjects();
 *      У которой в цикле для всех наблюдателей вызывается функция-событие HandleInsideCheck.
 *      Если проверка вернула true, то возвращаем указатель на этот DestroyableGroundObject в класс SBomber для подсчёта очков
 *      за уничтожение объекта и удаление объекта из массива статических объектов.
 *      Если ни один объект не был уничтожен, пусть возвращается nullptr.
 *      То есть необходимо переделать функцию:
 *      void SBomber::CheckDestoyableObjects(Bomb * pBomb)
 *      перенеся эту функциональность в класс Bomb.
 *
 *      А также, нужно изменить следующую функцию, откуда будет вызываться вышестоящая функция:
 *      void SBomber::CheckBombsAndGround()
 *
 *  P.S.
 *      Реализованы интерфейсные классы: class IObserver, class ISubject.
 *
 *      Добавлено наследование class Bomb : public DynamicObject, public Lesson_05::ISubject.
 *      В класс Bomb добавлен вектор <DestroyableGroundObject*> и реализованы override методы интерфейса ISubject.
 *
 *      Добавлено наследование class DestroyableGroundObject : public GameObject, public Lesson_05::IObserver.
 *
 *      Реализован override метод bool Tank::HandleInsideCheck(double, double) const override;
 *      Реализован override метод bool House::HandleInsideCheck(double, double) const override;
 *
 *      Изменены методы class SBomber:
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
