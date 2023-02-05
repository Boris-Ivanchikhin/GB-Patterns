
#ifndef BOMB_ITERATOR_H
#define BOMB_ITERATOR_H

#include <iostream> // header in standard library
#include <vector>

#include "include/DynamicObject.h"
#include "include/Bomb.h"

/* =============================================================================================
 * *** Lesson 03.  Patterns: Strategy, Iterator, Adapter
 *
 *  1. Применить шаблон «Итератор» в игре SBomber
 *
 *      C помощью паттерна «Итератор» искать и обходить всех бомбы в массиве динамических объектов.
 *      В классе SBomber есть функция FindAllBombs:
 *
 *      vector<Bomb*> SBomber::FindAllBombs() const
 *      {
 *          vector<Bomb*> vecBombs;
 *          for (size_t i = 0; i < vecDynamicObj.size(); i++)
 *          {
 *              Bomb* pBomb = dynamic_cast<Bomb*>(vecDynamicObj[i]);
 *              if (pBomb != nullptr)
 *              {
 *                  vecBombs.push_back(pBomb);
 *              }
 *          }
 *          return vecBombs;
 *      }
 *
 *      Можно для неё использовать паттерн «Итератор» и вынести сам алгоритм поиска бомб в массиве динамических объектов.
 *      Назвать класс можно BombIterator. Также можно добавить в класс SBomber функции begin и end, которые будут использоваться в FindAllBombs.
 *      Возвращение массива бомб можно оставить, как в функции SBomber::CheckBombsAndGround(). Если бомба пересекла линию земли,
 *      она удаляется из массива динамических объектов, что может нарушить работу итератора по этому же массиву.
 *
 *      void SBomber::CheckBombsAndGround()
 *      {
 *          vector<Bomb*> vecBombs = FindAllBombs();
 *          Ground* pGround = FindGround();
 *          const double y = pGround->GetY();
 *          for (size_t i = 0; i < vecBombs.size(); i++)
 *          {
 *          if (vecBombs[i]->GetY() >= y) // Пересечение бомбы с землей
 *              {
 *              pGround->AddCrater(vecBombs[i]->GetX());
 *              CheckDestoyableObjects(vecBombs[i]);
 *              DeleteDynamicObj(vecBombs[i]);
 *              }
 *          }
 *      }
 *
 * ============================================================================================= */

using namespace std;

class BombIterator
{
private:
    vector <DynamicObject*> &objects;
    int position;
    Bomb *ptr;

public:
    BombIterator (vector<DynamicObject*>& _objects)
    : objects (_objects), position (-1), ptr (nullptr)
    {
        ++(*this);
    };

    ~BombIterator() = default;

    void reset()
    {
        position = -1;
        ptr = nullptr;
    };

    // prefix increment
    BombIterator& operator++ ();

    // prefix decrement
    BombIterator& operator-- ();

    // iterator dereference operation
    Bomb& operator * ()
    {
        return *dynamic_cast <Bomb*> (objects.at(position));
    };

    // checking for logical equality of iterators
    bool operator == (BombIterator it)
    {
        if (position == it.position &&
            ptr == it.ptr &&
            objects == it.objects)
        {
            return true;
        }
        return false;
    };

    // checking for logical inequality of iterators
    bool operator != (BombIterator it)
    {
        return !(*this == it);
    };
};


#endif //BOMB_ITERATOR_H
