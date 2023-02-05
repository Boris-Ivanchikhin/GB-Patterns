#pragma once
#include <cstdint>

class GameObject {
public:

    GameObject() : x(0.0), y(0.0), width(0) { }

    virtual void Draw() const = 0;

    virtual inline void SetPos(double nx, double ny) { x = nx; y = ny; }

    virtual inline double GetY() const { return y; }
    virtual inline double GetX() const { return x; }

    virtual inline void SetWidth(uint16_t widthN) { width = widthN; }
    virtual inline uint16_t GetWidth() const { return width; }

protected:

    double x, y;
    uint16_t width;
};