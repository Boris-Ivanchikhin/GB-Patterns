#pragma once

#include "DynamicObject.h"

class Bomb : public DynamicObject
{
public:

	static const uint16_t BombCost = 10; // the cost of the bomb in points scored

	void Draw() const override;

private:

};

/* =============================================================================================
 * *** Lesson 02.  Patterns: Abstract factory, Command, Decorator
 *
 *  2.(*) Применение шаблона «Декоратор» в игре SBomber
 *      Задача: создание нового варианта бомбы в игре с помощью паттерна «Декоратор».
 *      Для класса Bomb создадим класс «Декоратор», который заставит бомбу падать быстрее и добавит при её рисовании новые графические элементы.
 *      Пусть класс декоратора называется BombDecorator и будет наследником DynamicObject, как и Bomb.
 *      Пусть класс-декоратор содержит объект «Бомба». Ему также необходимо переопределять (override) методы Move и Draw
 *      и вызывать эти методы у бомбы, которую он содержит.
 *
 * ============================================================================================= */

class BombDecorator: public DynamicObject
{
private:
    DynamicObject *bomb;

public:
    BombDecorator(DynamicObject *_bomb) : bomb(_bomb)
    {};
    ~BombDecorator () = default;

    void Move(uint16_t time) override;
    void Draw() const override;

};