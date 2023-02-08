#pragma once

#include <stdio.h>
#include <vector>

#include "include/DestroyableGroundObject.h"
#include "include/MyTools.h"

class House : public DestroyableGroundObject
{
public:

	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; };

	void Draw() const override;

    virtual void info() const
    {
        cout << "standard house" << endl;
    };


private:

	const uint16_t score = 40;

protected:

    inline void DrawFigure(MyTools::ScreenSingleton&) const;
};

/* =============================================================================================
 * *** Lesson 04.  Patterns: Factory Method, Builder, Bridge
 *
 *  1. Примените паттерн «Строитель» (Builder) для создания разных вариантов домов в игре.
 *
 * ============================================================================================= */

namespace Lesson_04
{

    class GreenHouse : public House
    {
    public:

        void Draw() const override;

        void info() const override
        {
            cout << "green house" << endl;
        };

    };

    class RedHouse : public House {
    public:

        void Draw() const override;

        void info() const override
        {
            cout << "red house" << endl;
        };
    };

    struct City
    {
        vector<House *> buildings;

        virtual ~City()
        {
            for (const auto &_build: buildings)
                delete _build;
        };

        void info() const
        {
            for (const auto &_build: buildings)
                _build->info();
        };
    };

    class CityBuilder
    {
    protected:
        City *city;

    public:
        CityBuilder() : city(nullptr) {};

        virtual ~CityBuilder()
        {
            if (city)
                delete city;
        };

        virtual void CreateCity() {};

        virtual void BuildRedHouse() {};

        virtual void BuildGreenHouse() {};

        virtual City *GetCity() { return city; };
    };

    class RedCityBuilder : public CityBuilder
    {
    public:
        void CreateCity() override
        {
            if (city)
                delete city;

            city = new City;
        };

        void BuildRedHouse() override
        {
            city->buildings.emplace_back(new RedHouse);
        };

    };

    class GreenCityBuilder : public CityBuilder
    {
    public:
        void CreateCity() override
        {
            if (city)
                delete city;

            city = new City;
        };

        void BuildGreenHouse() override
        {
            city->buildings.emplace_back(new GreenHouse);
        };

    };

    class Supervisor
    {
    public:
        City *CreateCity(CityBuilder &builder)
        {
            builder.CreateCity();
            builder.BuildRedHouse();
            builder.BuildGreenHouse();
            // return
            return builder.GetCity();
        };
    };

    void BuildExample ();

};