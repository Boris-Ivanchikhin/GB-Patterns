
#include <iostream>

#include "Plane.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

void Plane::Draw() const
{
    MyTools::SetColor(CC_LightBlue);
    GotoXY(x, y);
    cout << "=========>";
    GotoXY(x - 2, y - 1);
    cout << "===";
    GotoXY(x + 3, y - 1);
    cout << "\\\\\\\\";
    GotoXY(x + 3, y + 1);
    cout << "////";
}
