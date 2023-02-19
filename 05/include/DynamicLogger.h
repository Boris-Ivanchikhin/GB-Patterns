#ifndef DYNAMIC_LOGGER_H
#define DYNAMIC_LOGGER_H

/* =============================================================================================
 * *** Lesson 05.  Patterns: Facade, Visitor and Observer
 *
 *  1. Применение паттерна «Посетитель».
 *      Сделать логирование динамических объектов с помощью паттерна «Посетитель».
 *
 *  P.S.
 *      Логгирование события перемещение (Move): class MoveEventLogger
 *      Добавлен virtual метод: void DynamicObject::Report(class Lesson_05::IEventLogger*)
 *      Добавлен override метод: void Bomb::Report(Lesson_05::IEventLogger *)
 *      Добавлен override метод: void Plane::Report(Lesson_05::IEventLogger *)
 *      Изменён метод: void SBomber::MoveObjects()
 *
 * ============================================================================================= */

#include <iostream>
#include "include/MyTools.h"

class Bomb;
class Plane;

using namespace std;

namespace Lesson_05
{

    class IEventLogger
    {
    private:
        MyTools::LoggerSingleton& instance;

    public:
        IEventLogger() : instance(MyTools::LoggerSingleton::getInstance()) {};

        virtual void WriteEvent(Bomb *) = 0;
        virtual void WriteEvent(Plane *) = 0;

    protected:
        void __fastcall WriteToLog(const string &);
    };

    class MoveEventLogger : public IEventLogger
    {
    public:
        MoveEventLogger() : IEventLogger () {};
        
        void __fastcall WriteEvent(Bomb* ) override;
        void __fastcall WriteEvent(Plane* ) override;
    };

};

#endif // DYNAMIC_LOGGER_H
