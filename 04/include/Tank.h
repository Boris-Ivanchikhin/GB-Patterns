#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"


class Tank : public DestroyableGroundObject
{
public:

	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() const override;

private:

	const uint16_t score = 30;
};


/* =============================================================================================
 * *** Lesson 03.  Patterns: Strategy, Iterator, Adapter
 *
 *  2.(*) Применить шаблон «Адаптер»
 *
 *      Адаптировать несовместимый по интерфейсам класс в игре SBomber с помощью паттерна «Адаптер».
 *      Посмотрим на диаграмму классов проекта SBomber (раздел 2). Обратим внимание на классы: GameObject, DestroyableGroundObject и Tank.
 *      Допустим, класс Tank был реализован независимо от нашего проекта SBomber, имеет несовместимый интерфейс и название TankAdaptee.
 *      Перенесём в него всю функциональность из класса GameObject и добавим другие интерфейсные функции: isInRange и Paint вместо isInside и Draw.
 *
 *      class TankAdaptee
 *      {
 *      public:
 *          TankAdaptee() : x(0.0), y(0.0), width(0) { }
 *          void Paint();
 *          bool __fastcall isInRange(double x1, double x2) const;
 *          inline uint16_t GetScore() const { return score; }
 *
 *          inline void SetPos(double nx, double ny) { x = nx; y = ny; }
 *          inline double GetY() const { return y; }
 *          inline double GetX() const { return x; }
 *
 *          inline void SetWidth(uint16_t widthN) { width = widthN; }
 *          inline uint16_t GetWidth() const { return width; }
 *
 *      protected:
 *          double x, y;
 *          uint16_t width;
 *          const uint16_t score = 30;
 *      };
 *
 *      Для использования в нашей игре класс нужно адаптировать, не изменяя его. Создадим для него класс-обёртку TankAdapter —
 *      наследник класса DestroyableGroundObject, который должен содержать экземпляр tank класса TankAdaptee.
 *      Также в GameObject сделаем виртуальными следующие функции:
 *
 *      void SetPos(double nx, double ny) { x = nx; y = ny; }
 *      double GetY() const { return y; }
 *      double GetX() const { return x; }
 *      void SetWidth(uint16_t widthN) { width = widthN; }
 *      uint16_t GetWidth() const { return width; }
 *
 *      Переопределим их в «Адаптере», чтобы они взаимодействовали с теми же функциями адаптируемого класса TankAdaptee. Например:
 *
 *      void TankAdapter::SetPos(double nx, double ny)
 *      {
 *          tank.SetPos(nx, ny);
 *      }
 *
 *      uint16_t TankAdapter::GetWidth() const
 *      {
 *          return tank.GetWidth();
 *      }
 *
 *      void TankAdapter::Draw() const
 *      {
 *          tank.Paint();
 *      };
 *
 *      bool __fastcall TankAdapter::isInside(double x1, double x2) const
 *      {
 *          tank.isInRange(x1, x2);
 *      };
 *
 *      Нам нужно полностью обернуть объект класса TankAdaptee и адаптировать его, не ломая уже реализованное поведение танков в игре.
 *      Танки для нашего уровня — объекты класса TankAdapter — мы будем создавать в конструкторе класса SBomber.
 *      И они будут корректно работать, потому что включены в нашу иерархию классов, где есть совместимый интерфейс с поддержкой полиморфизма.
 *
 * ============================================================================================= */

class TankAdaptee
{
public:

    TankAdaptee() : x(0.0), y(0.0), width(0) { }

    void Paint() const;
    bool __fastcall isInRange(double x1, double x2) const;

    inline uint16_t GetScore() const { return score; }

    inline void SetPos(double nx, double ny) { x = nx; y = ny; }
    inline double GetY() const { return y; }
    inline double GetX() const { return x; }

    inline void SetWidth(uint16_t widthN) { width = widthN; }
    inline uint16_t GetWidth() const { return width; }

protected:

    double x, y;
    uint16_t width;
    const uint16_t score = 30;
};


class TankAdapter : public DestroyableGroundObject
{
private:
    TankAdaptee *tank;

public:

    TankAdapter() : DestroyableGroundObject() {tank = new TankAdaptee();};
    ~TankAdapter() {delete tank;};

    void Draw() const {tank->Paint();};

    bool __fastcall isInRange(double x1, double x2) const;

    inline uint16_t GetScore() const {return tank->GetScore();};

    inline double GetY() const override {return tank->GetY();};
    inline double GetX() const override {return tank->GetY();};

    uint16_t GetWidth() const override {return tank->GetWidth();};
    void SetWidth(uint16_t widthN) override {tank->SetWidth(widthN);};

    void SetPos(double nx, double ny) override {tank->SetPos(nx, ny);};

    bool isInside(double x1, double x2) const override {
        return tank->isInRange(x1, x2);
    };
};
