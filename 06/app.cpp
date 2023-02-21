// *** Course: GOF Design Patterns
// *** Lesson 06.  Patterns: Composite, Mediator and Template method

#include <conio.h>

#include "include/SBomber.h"
#include "include/MyTools.h"

using namespace std;

// Function called at shutdown
void endFunction ()
{
    // Output of the shutdown message
    puts ("\nthe work is completed!");
} // endFunction

//========================================================================================================================

int main(void)
{
    // Russian language in the console
    setlocale (LC_ALL, "");

    // Registration of the function to be called during normal shutdown
    if (atexit (endFunction)) {
        // Checking the registration of the endFunction
        puts ("post- function registration error!");
    }

    MyTools::Lesson_01::LoggerSingleton::getInstance().OpenLogFile("log.txt");

    SBomber game;

    do {
        game.TimeStart();

        if (_kbhit())
        {
            game.ProcessKBHit();
        }

        MyTools::Lesson_01::ScreenSingleton::getInstance().ClrScr();

        game.DrawFrame();
        game.MoveObjects();
        game.CheckObjects();

        game.TimeFinish();

    } while (!game.GetExitFlag());

    MyTools::Lesson_01::LoggerSingleton::getInstance().CloseLogFile();

    // return o.k.
    return EXIT_SUCCESS;
}
