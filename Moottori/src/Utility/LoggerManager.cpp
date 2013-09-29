#include "Utility/LoggerManager.h"

std::string LoggerManager::mLogFolder = "";

std::string LoggerManager::GetFullName( const std::string &name )
{
	return mLogFolder + "/" + name;	return name;
}

Logger & LoggerManager::GetLog( std::string name )
{
	name = GetFullName(name);

	if (mLogs.count(name) == 0)
	{
		mLogs[name].reset(new Logger());
		mLogs[name]->Open(name);
		mLogs[name]->AddTimeStamps(true);
		mLogs[name]->SetLoggingLevel(LogLevel::All);
	}

	return *mLogs[name];
}

void LoggerManager::Release()
{
	mLogs.clear();
}

LoggerManager::LoggerManager()
{

}

void LoggerManager::SetLogFolder( std::string folder )
{
	mLogFolder = folder;
}

LoggerManager::~LoggerManager()
{
	mLogs.clear();
}
