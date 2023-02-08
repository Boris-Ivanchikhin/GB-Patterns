//
// Created by Boris Ivanchikhin on 04.02.2023.
//

#include "include/BombIterator.h"

// prefix increment
BombIterator& BombIterator::operator++ ()
{
    position++;

    if (position == -1)
        position = 0;

    for(; position < objects.size(); position++)
    {
        Bomb *pBomb = dynamic_cast <Bomb*> (objects[position]);
        if (pBomb != nullptr)
        {
            ptr = pBomb;
            break;
        }
    }

    if (position == objects.size())
    {
        position = -1;
        ptr = nullptr;
    }

    // return
    return *this;
};

// prefix decrement
BombIterator& BombIterator::operator-- ()
{
    if (position == -1)
        position = objects.size() - 1;
    for (; position >= 0; position--)
    {
        Bomb *pBomb = dynamic_cast <Bomb*> (objects[position]);
        if (pBomb != nullptr)
        {
            ptr = pBomb;
            break;
        }
    }

    if (position == -1)
        ptr = nullptr;

    // return
    return *this;
}