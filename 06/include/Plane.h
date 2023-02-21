#pragma once

#include "DynamicObject.h"
#include "MyTools.h"

using namespace MyTools;

/* =============================================================================================
 * *** Lesson 06.  Patterns: Composite, Mediator and Template method
 *
 *  2(*). Применение паттерна « Шаблонный метод».
 *      Задача: использовать паттерн « Шаблонный метод» при рисовании самолёта.
 *      Сделаем функцию рисования самолёта (Plane::Draw()) шаблонным методом,
 *      который вызывает функции рисования фюзеляжа (DrawBody), рисования крыльев (DrawWings) и хвоста (DrawTail).
 *      Создадим двух наследников класса Plane: ColorPlane и BigPlane. В них переопределяются указанные выше три функции так,
 *      что класс ColorPlane рисует разные части самолёта разными цветами, используя функцию установки цвета:
 *
 *      MyTools::SetColor(CC_LightBlue);
 *
 *      А класс BigPlane рисует самолёт немного увеличенного размера.
 *      В конструкторе класса SBomber будем генерировать случайное число, от которого будет зависеть, какой из двух
 *      типов самолёта (ColorPlane или BigPlane) мы будем добавлять в игру в начале.
 *
 *  P.S.
 *
 *      class Plane :
 *      - добавлен virtual void DrawBody(Lesson_01::ScreenSingleton& ) const;
 *      - добавлен virtual void DrawTail(Lesson_01::ScreenSingleton& ) const;
 *      - добавлен void DrawWings(Lesson_01::ScreenSingleton& ) const;
 *      - изменён void Draw() const override;
 *
 *      Создан class ColorPlane
 *      Создан class BigPlane
 *
 * ============================================================================================= */

class Plane : public DynamicObject
{
protected:
    virtual void DrawBody(Lesson_01::ScreenSingleton& ) const;
    virtual void DrawTail(Lesson_01::ScreenSingleton& ) const;
    virtual void DrawWings(Lesson_01::ScreenSingleton& ) const;

public:

    void Draw() const override;

    inline void ChangePlaneY(double dy) { yDirection += dy; }

private:

};

namespace Lesson_06
{
    class ColorPlane : public Plane
    {
    public:
        void Draw() const final override;
    };

    class BigPlane : public Plane
    {
    protected:
        void __fastcall DrawBody(Lesson_01::ScreenSingleton& ) const override;
        void __fastcall DrawTail(Lesson_01::ScreenSingleton& ) const override;
        void __fastcall DrawWings(Lesson_01::ScreenSingleton& ) const override;

    public:

    };

}

