#ifndef TREE_H
#define TREE_H

#include <stdint.h>
#include <iostream>

#include "include/DestroyableGroundObject.h"

class TreeA : public DestroyableGroundObject
{
public:

    bool __fastcall isInside(double x1, double x2) const override;

    inline uint16_t GetScore() const override { return score; }

    void Draw() const override;

private:

    const uint16_t score = 10;

};

class TreeB : public DestroyableGroundObject
{
public:

    bool __fastcall isInside(double x1, double x2) const override;

    inline uint16_t GetScore() const override { return score; }

    void Draw() const override;

private:

    const uint16_t score = 20;

};

class ITreeCreator
{
public:
    virtual DestroyableGroundObject* Create() = 0;
    virtual ~ITreeCreator() {};
};

class TreeCreatorA : public ITreeCreator
{
public:
    DestroyableGroundObject *Create() override
    {
        return new (std::nothrow) TreeA;
    };
    //~TreeCreatorA() override {};
};

class TreeCreatorB : public ITreeCreator
{
public:
    DestroyableGroundObject *Create() override
    {
        return new (std::nothrow) TreeB;
    };
    //~TreeCreatorB() override {};
};





#endif //TREE_H
