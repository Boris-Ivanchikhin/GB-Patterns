
#include "include/FileLogger.h"
#include "include/MyTools.h"

using namespace MyTools;

namespace Lesson_07
{
    FileLogger logger{};

    void FileLogger::OpenLogFile(const string &FN) {
        logOut.open(FN, ios_base::out);
    }

    FileLogger::FileLogger() {
        OpenLogFile("log.txt");
    }

    void FileLogger::CloseLogFile() {
        if (logOut.is_open()) {
            logOut.close();
        }
    }

    FileLogger::~FileLogger() {
        CloseLogFile();;
    }

    void FileLogger::WriteToLog(const string &str) {
        if (logOut.is_open()) {
            logOut << GetCurDateTime() << " - " << str << endl;
        }
    }

    void FileLogger::WriteToLog(const string &str, int n) {
        if (logOut.is_open()) {
            logOut << GetCurDateTime() << " - " << str << n << endl;
        }
    }

    void FileLogger::WriteToLog(const string &str, double d) {
        if (logOut.is_open()) {
            logOut << GetCurDateTime() << " - " << str << d << endl;
        }
    }

}