#include "DynamicLogger.h"
#include "include/Bomb.h"
#include "include/Plane.h"

namespace Lesson_05
{
    void IEventLogger::WriteToLog(const string &message)
    {
        instance.WriteToLog(message);
    }

    void MoveEventLogger::WriteEvent(Bomb *obj)
    {
        string msg = "the new position of the Bomb -> X: " + to_string(obj->GetX()) +
                        ", Y: " + to_string(obj->GetY());
        WriteToLog(msg);
    }

    void MoveEventLogger::WriteEvent(Plane *obj)
    {
        string msg = "the new position of the Plane -> X: " + to_string(obj->GetX()) +
                     ", Y: " + to_string(obj->GetY());
        WriteToLog(msg);
    }
}
