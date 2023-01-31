#pragma once

#include <stdint.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

namespace MyTools {

    // Color palette from 0 to 15
    enum ConsoleColor
    {
        CC_Black = 0,
        CC_Blue,
        CC_Green,
        CC_Cyan,
        CC_Red,
        CC_Magenta,
        CC_Brown,
        CC_LightGray,
        CC_DarkGray,
        CC_LightBlue,
        CC_LightGreen,
        CC_LightCyan,
        CC_LightRed,
        CC_LightMagenta,
        CC_Yellow,
        CC_White
    };

    string GetCurDateTime();

	//=============================================================================================

    // * class ScreenSingleton

    // void ClrScr();
    // void __fastcall GotoXY(double x, double y);
    // uint16_t GetMaxX();
    // uint16_t GetMaxY();
    // void SetColor(ConsoleColor color);

    class ScreenSingleton
    {
    public:

        static ScreenSingleton& getInstance()
        {
            static ScreenSingleton _instance;
            return _instance;
        }
        void ClrScr();
        void __fastcall GotoXY(double x, double y);
        uint16_t GetMaxX();
        uint16_t GetMaxY();
        void SetColor(ConsoleColor color);

        ~ScreenSingleton() = default;

    private:

        ScreenSingleton() = default;
        ScreenSingleton(const ScreenSingleton& root) = delete;
        ScreenSingleton& operator=(const ScreenSingleton&) = delete;
    }; // * class ScreenSingleton

    /* =============================================================================================
     * *** Lesson 01:  Singleton and Proxy patterns.
     *
     *  1. Применение паттерна Singleton.
     *      Задача: применить паттерн «Одиночка» для логирования событий в проекте SBomber (рефакторинг модуля MyTools.cpp).
     *      В единице трансляции MyTools.cpp есть вторая группа функций (помимо функций для работы с экраном)
     *      для логирования событий в проекте SBomber:
     *
     *      void __fastcall OpenLogFile(const std::string& FN);
     *      void CloseLogFile();
     *      void __fastcall WriteToLog(const std::string& str);
     *      void __fastcall WriteToLog(const std::string& str, int n);
     *      void __fastcall WriteToLog(const std::string& str, double d);
     *
     *      Видим функции, которые открывают и закрывают файл для ведения лога, и 3 функции для записи данных в лог-файл.
     *      Необходимо выполнить рефакторинг этих функций и поместить их внутрь «Одиночки» (FileLoggerSingleton)
     *      по аналогии с тем, как это было сделано выше для объекта-одиночки ScreenSingleton.
     *      Так мы сможем использовать эту функциональность в стиле ООП.
     *
     * ============================================================================================= */

    class ILogger
    {
    public:

        virtual void OpenLogFile(const string&) = 0;
        virtual void CloseLogFile() = 0;
        virtual void WriteToLog(const string&) = 0;
        virtual void WriteToLog(const string&, int) = 0;
        virtual void WriteToLog(const string&str, double) = 0;

        ILogger() = default;
        virtual ~ILogger() = default;
    }; // class ILogger

    class FileLoggerSingleton: public ILogger
    {
    public:

        static FileLoggerSingleton& getInstance()
        {
            static FileLoggerSingleton _instance;
            return _instance;
        };

        ofstream& getLogOut();

        void __fastcall OpenLogFile(const string&) override;
        void CloseLogFile() override;
        void __fastcall WriteToLog(const string&) override;
        void __fastcall WriteToLog(const string&, int) override;
        void __fastcall WriteToLog(const string&, double) override;

        ~FileLoggerSingleton() = default;

    private:

        FileLoggerSingleton() = default;
        FileLoggerSingleton(const FileLoggerSingleton&) = delete;
        FileLoggerSingleton& operator=(const FileLoggerSingleton&) = delete;
        FileLoggerSingleton& operator=(FileLoggerSingleton&&) = delete;

        ofstream logOut;
    }; // class FileLoggerSingleton

    /* =============================================================================================
     * *** Lesson 01:  Singleton and Proxy patterns.
     *
     *  2.(*) Применение паттерна «Заместитель»
     *      Задача: использовать паттерн «Заместитель» в проекте SBomber в алгоритмах логирования.
     *      Используйте структурный паттерн «Заместитель» в проекте SBomber в качестве обёртки для процедуры логирования
     *      в файл через FileLoggerSingleton. Пусть в начало строки логирования обёртка добавляет номер логируемого события, начиная с 1.
     *      Дайте название LoggerSingleton — его тоже можно сделать «Одиночкой».
     *      Возможно, в будущем мы захотим управлять записью логов в файл, по сети или в БД.
     *      Тогда мы быстро усовершенствуем LoggerSingleton: добавим другие виды логирования и возможность переключения между ними.
     *      Остальной код, который пользуется этим классом, трогать не придётся.
     * ============================================================================================= */

    class LoggerSingleton: public ILogger
    {
    public:
        static LoggerSingleton& getInstance()
        {
            static LoggerSingleton _instance;
            return _instance;
        };

        void __fastcall OpenLogFile(const string&) override;
        void CloseLogFile() override;
        void __fastcall WriteToLog(const string&) override;
        void __fastcall WriteToLog(const string&, int) override;
        void __fastcall WriteToLog(const string&, double) override;

    private:
        LoggerSingleton() : _logger (FileLoggerSingleton::getInstance()), count (0) {};

        LoggerSingleton(const LoggerSingleton&) = delete;
        LoggerSingleton& operator=(const LoggerSingleton&) = delete;
        LoggerSingleton& operator=(LoggerSingleton&&) = delete;

        FileLoggerSingleton&_logger;
        unsigned long count;
    }; // class LoggerSingleton

}; // namespace MyTools