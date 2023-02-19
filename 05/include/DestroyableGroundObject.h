#pragma once

#include <stdint.h>

#include "include/GameObject.h"
#include "include/BombObserver.h"

class DestroyableGroundObject : public GameObject, public Lesson_05::IObserver
{
public:

    virtual bool __fastcall isInside(double x1, double x2) const = 0;

    virtual inline uint16_t GetScore() const = 0;

    virtual bool HandleInsideCheck (double, double) const = 0;

protected:

};