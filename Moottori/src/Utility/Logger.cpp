#include <ctime>
#include "Utility\Logger.h"


Logger::Logger(std::string fileName, LogLevel loggingLevel) : mLoggingLevel(loggingLevel), mTimeStamps(false), mLogFile()
{
    if (mLoggingLevel > LogLevel::None)
        Open(fileName);
}
Logger::Logger() : mLoggingLevel(LogLevel::None), mTimeStamps(false), mLogFile()
{

}
Logger::~Logger()
{
    Close();
}

void Logger::Open(std::string fileName)
{
    Close();
    mLogFile.open(fileName);
    mLogFile << CreateStamp(true) << "Opening new log file\n\n";
}

void Logger::Close()
{
    if (mLogFile.is_open())
    {
        mLogFile << "\n" << CreateStamp(true) << "Closing log file\n";
        mLogFile.close();
    }
}

void Logger::AddTimeStamps(bool stamp) throw()
{
    mTimeStamps = stamp;
}

std::string Logger::CreateStamp(bool initializeStamp) throw()
{
    time_t currentTime;
    time(&currentTime);
    tm *timeInfo = localtime(&currentTime);

    std::ostringstream stamp;
    stamp << "[";
    if (initializeStamp == true)
    {
        stamp << timeInfo->tm_year + 1900 << "." <<  timeInfo->tm_mon + 1 << "." << timeInfo->tm_mday << " ";
    }
    stamp << (timeInfo->tm_hour < 10 ? "0" : "") <<  timeInfo->tm_hour << ":" << (timeInfo->tm_min < 10 ? "0" : "") <<  timeInfo->tm_min << ":" << (timeInfo->tm_sec < 10 ? "0" : "")  << timeInfo->tm_sec << "]";
    stamp << " ";
    return stamp.str();
}

void Logger::AddLine( LogLevel level, std::string text )
{
	if (level > mLoggingLevel || mLoggingLevel == LogLevel::None)
		return;

	if (mTimeStamps == true)
		mLogFile << CreateStamp() << " ";

	switch (level)
	{
	case LogLevel::None:
	case LogLevel::All:
		break;
	case LogLevel::Error:
		mLogFile << "Error: ";
		break;
	case LogLevel::Warning:
		mLogFile << "Warning: ";
		break;
	case LogLevel::Info:
		mLogFile << "Info: ";
		break;
	case LogLevel::Debug:
		mLogFile << "Debug: ";
		break;
	default:
		mLogFile << "Logger error: Level " << static_cast<int>(level) << " given which is undefined. Following message attached: ";
	}
	mLogFile << text << std::endl;
}
