#pragma once

#include "DynamicObject.h"

/* =============================================================================================
 * *** Lesson  08. Patterns: State and Prototype
 *
 * 1.  Паттерн «Прототип».
 *      Задача: применить паттерн «Прототип» в проекте SBomber для клонирования в runtime бомб.
 *      Если у самолета доступные бомбы, по нажатию клавиши ‘d’ бросать бомбу и клонировать её с немного смещенными по х координатами.
 *      Клонирование реализовать в классе Bomb.
 *
 *     P.S.
 *      В class Bomb добавлены:
 *      - конструктор копирования Bomb(const Bomb& );
 *      - метод Bomb* clone() const;
 *
 * ============================================================================================= */

class Bomb : public DynamicObject
{
public:
    Bomb() = default;
    ~Bomb() = default;

    Bomb(const Bomb& );

	static const uint16_t BombCost = 10;

	void Draw() const override;

    Bomb* clone() const
    {
        return new Bomb(*this);
    };

private:

};

