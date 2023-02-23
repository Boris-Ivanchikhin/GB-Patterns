#ifndef FILE_LOGGER
#define FILE_LOGGER

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/* =============================================================================================
 // *** Lesson  07. Patterns: Memento, RAII and PIMPL
 *
 * 1.  Применить паттерн RAII для функций логирования.
 *      Задача: Возьмём самую первую версию исходного кода проекта SBomber, где мы ещё не использовали паттерн «Одиночки» (Singleton).
 *      В файле SBomberProject.cpp посмотрим на функцию main. В её начале мы вызываем:
 *
 *      MyTools::OpenLogFile("log.txt");
 *
 *      А в конце:
 *
 *      MyTools::CloseLogFile();
 *
 *      Такой подход к логированию в файл небезопасен по двум причинам. Во-первых, программист может забыть вызвать функцию
 *      закрытия файла по ошибке. Во-вторых, если после открытия файла в процессе игры возникнет исключение,
 *      функция закрытия файла вызвана не будет. Можно сделать более безопасную реализацию логирования с использованием
 *      шаблона RAII. Для этого нужно перенести открытие лог-файла в конструктор, а закрытие, соответственно, — в деструктор.
 *      Также перенесём в этот класс и остальные функции, которые участвуют в логировании.
 *      В этом файле создадим глобальный объект FileLogger logger, через который будем вести лог игры.
 *      Вспомним, что для доступа к нему из других единиц трансляции (файлов .cpp), необходима директива extern.
 *
 *  P.S.
 *      Создан class FileLogger в который перенесены (из MyTools .h .cpp):
 *      - ofstream logOut;
 *      - void __fastcall OpenLogFile(const string &);
 *      - void CloseLogFile();
 *      - void __fastcall WriteToLog(const string &);
 *      - void __fastcall WriteToLog(const string &, int);
 *      - void __fastcall WriteToLog(const string &, double);
 *
 *      Внесены изменения :
 *      - int main(void);
 *      - методы класса SBomber, использующие WriteToLog.
 *
 * ============================================================================================= */

namespace Lesson_07
{
    class FileLogger {
        ofstream logOut;

        void __fastcall OpenLogFile(const string &);

        void CloseLogFile();

    public:
        FileLogger();

        ~FileLogger();

        void __fastcall WriteToLog(const string &);

        void __fastcall WriteToLog(const string &, int);

        void __fastcall WriteToLog(const string &, double);

    };

    extern FileLogger logger;
}

#endif //FILE_LOGGER
