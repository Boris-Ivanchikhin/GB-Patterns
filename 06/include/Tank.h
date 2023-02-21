#pragma once

#include <stdint.h>
#include <iostream>
#include <chrono>

#include "DestroyableGroundObject.h"
#include "LevelGUI.h"

using namespace std;

/* =============================================================================================
 * *** Lesson 06.  Patterns: Composite, Mediator and Template method
 *
 *  1.  Применение паттерна «Посредник».
 *      Задача: использовать паттерн « Посредник» для организации взаимодействия каких-либо объектов в игре.
 *      Паттерн « Посредник» мог бы использоваться для организации текстового чата между игроками по сети.
 *      Но для этого необходимо довольно сложное сетевое взаимодействие. Поэтому упростим задачу.
 *      Предположим, что объекты «Танки» обладают искусственным интеллектом и нужно сделать так,
 *      чтобы они могли посылать текстовые сообщения на экран пользователя: например, шуточные угрозы для самолёта,
 *      который их атакует. Необходимо сделать в классе LevelGUI очередь полученных сообщений для вывода на экран.
 *      Ставить сообщения в очередь будет объект класса Mediator. Он же будет находиться в каждом объекте «Танк»
 *      (можно сделать поле статическим указателем). При рисовании танка будем бросать кубик и с определённой вероятностью
 *      посылать какое-либо сообщение для пилота самолёта (пользователя) через посредника объекту LevelGUI.
 *      При рисовании GUI через LevelGUI::Draw() будем извлекать первое сообщение из очереди и выводить его
 *      на нижнюю часть экрана какое-то небольшое время (3-5 сек). После чего извлекаем следующее сообщение из очереди.
 *
 *  P.S.
 *      Создан class TankMediator
 *
 *      class Tank :
 *      - добавлен mutable chrono::time_point<clock_t> start;
 *      - добавлен const long Timeout = 3.0; // seconds
 *      - добавлен double Elapsed() const
 *      - добавлен static Lesson_06::TankMediator* mediator;
 *      - добавлен static void SetMediator (class Lesson_06::TankMediator* _mediator)
 *      - добавлен Tank (class Lesson_06::TankMediator* _mediator = nullptr)
 *      - изменён void Tank::Draw() const
 *
 *      class LevelGUI :
 *      - добавлен mutable vector <string> messages;
 *      - добавлен optional<string> GetMessage () const;
 *      - добавлен void AddMessage (const string &msg)
 *      - изменён void LevelGUI::Draw() const
 *
 *      class SBomber :
 *      - добавлен Lesson_06::TankMediator* _mediator;
 *      - изменён SBomber::SBomber()
 *      - изменён SBomber::~SBomber()
 *
 * ============================================================================================= */

class Tank;

namespace Lesson_06
{

    class TankMediator
    {
    private:
        LevelGUI* GUI = nullptr;
    public:
        TankMediator(LevelGUI *_gui) : GUI(_gui) {};
        ~TankMediator() = default;

        void Notify(const string _msg)
        {
            if (GUI)
                GUI->AddMessage("Tank: " + _msg);
        };
    };

};

using namespace Lesson_06;

class Tank : public DestroyableGroundObject
{
private:
    using clock_t = chrono::high_resolution_clock;
    using second_t = chrono::duration<double, ratio<1>>;
    mutable chrono::time_point<clock_t> start;
    const long Timeout = 3.0; // seconds

    double Elapsed() const
    {
        return chrono::duration_cast<second_t>(clock_t::now() - start).count();
    };

    static Lesson_06::TankMediator* mediator;

public:
    static void SetMediator (class Lesson_06::TankMediator* _mediator)
    {
        if (_mediator)
            mediator = _mediator;
    };

    Tank (class Lesson_06::TankMediator* _mediator = nullptr)
    : start(clock_t::now())
    {
        SetMediator (_mediator);
    };


    bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() const override;

private:

	const uint16_t score = 30;

};





