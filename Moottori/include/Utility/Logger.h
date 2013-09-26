#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <string>
#include <fstream>
#include <sstream>

enum class LogLevel : int { None, Debug, Info, Warning, Error, All };

class Logger
{
    public:
        Logger(std::string fileName, LogLevel loggingLevel);
        Logger();
        virtual ~Logger();
        void Open(std::string fileName);
        void Close();
        void AddTimeStamps(bool stamp);

        void AddLine(LogLevel level, std::string text);
        void SetLoggingLevel(LogLevel val) { mLoggingLevel = val; }
    private:
        LogLevel mLoggingLevel;
        std::string CreateStamp(bool initializeStamp = false);
        bool mTimeStamps;
        std::ofstream mLogFile;
};

#endif // LOGGER_HPP
