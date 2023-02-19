#pragma once

#include "include/DynamicObject.h"

class Plane : public DynamicObject {
public:

    void Draw() const override;

    inline void ChangePlaneY(double dy) { yDirection += dy; }

    void Report(Lesson_05::IEventLogger *) override;

private:

};

