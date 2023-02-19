#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream> // header in standard library
#include <vector>

#include "include/DynamicObject.h"
#include "include/Plane.h"

using namespace std;

/* =============================================================================================
 * *** Lesson 02.  Patterns: Abstract factory, Command, Decorator
 *
 *  1. Применение шаблона «Команда» в игре SBomber
 *      Задача: применить паттерн «Команда» для выполнения частых стандартных действий в главном классе игры SBomber,
 *      таких как удаление динамических и статических объектов, бросание бомбы.
 *      В проекте SBomber уже есть функции, которые можно оформить как «Команды»:
 *
 *      void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
 *      void __fastcall DeleteStaticObj(GameObject* pObj);
 *      void DropBomb();
 *      std::vector<DynamicObject*> vecDynamicObj;
 *      std::vector<GameObject*> vecStaticObj;
 *
 *      Первые две команды будут получать указатели на удаляемый объект и ссылку на массивы, откуда его надо удалить.
 *      Для третьей команды можно передавать, константный указатель на объект Plane (из него команда будет брать координаты самолета),
 *      ссылку на массив динамических объектов объектов (для создания динамического объекта Bomb) и константную ссылку
 *      на количество бомб у самолета (количество доступных бомб хранится в объекте SBomber).
 *      Можно передавать ещё скорость падения и размер (ширину) воронки от взрыва — это позволит в будущем бросать более мощные бомбы,
 *      которые будут быстрее падать и оставлять больший след.
 *
 *      Функциональность из этих трёх функций можно для простоты перенести в команды. В этом случае получателем (Receiver)
 *      и исполнителем будет сама команда. Если потребуется выполнить какую-то команду внутри класса SBomber,
 *      мы будем динамически создавать эту команду, задавать ей параметры (SetParams) и передавать её функции-методу.
 *      Он, в свою очередь, будет вызывать для этой команды виртуальный метод Execute и удалять её из памяти.
 *      Отмена (Undo) действий или команд в нашей игре не нужна.
 *
 *      SBomber::CommandExecuter(AbstractCommand * pCommand);
 *
 * ============================================================================================= */

namespace Lesson_02
{
    template <class T>
    class AbstractCommand
    {
    protected:
        vector <T*> *vecObj;

    public:
        AbstractCommand ()
                : vecObj(nullptr) {};
        virtual ~AbstractCommand () = default;

        void SetVector(vector<T *> *_vecObj)
        {
            AbstractCommand::vecObj = _vecObj;
        };

        virtual void Execute() = 0;
    };

    template <class T>
    class CommandDeleteObj : public AbstractCommand <T>
    {
    private:
        T *pObj;

    public:
        CommandDeleteObj ()
                : AbstractCommand <T> (), pObj (nullptr)
        {};
        ~CommandDeleteObj () = default;

        void SetObject(T *_pObj)
        {
            pObj = _pObj;
        };

        void Execute() override;
    };

    template<class T>
    void CommandDeleteObj<T>::Execute() {

        if (!AbstractCommand <T>::vecObj || !pObj)
            return;

        auto it = AbstractCommand <T>::vecObj->begin();
        for (; it != AbstractCommand <T>::vecObj->end(); it++)
        {
            if (*it == pObj)
            {
                AbstractCommand <T>::vecObj->erase(it);
                break;
            }
        }
    };

    class CommandDropBomb : public AbstractCommand <DynamicObject>
    {
    private:
        Plane *pPlane;
        uint16_t bombsNumber;

    public:
        CommandDropBomb ()
                : AbstractCommand (), pPlane (nullptr), bombsNumber(0)
        {};
        ~CommandDropBomb () = default;

        void SetPlane(Plane *_pPlane)
        {
            pPlane = _pPlane;
        };

        void SetBombsNumber(const uint16_t &_bombsNumber)
        {
            bombsNumber = _bombsNumber;
        };

        void Execute() override;
    };
}

#endif //COMMANDS_H
