#include "Utility/LoggerManager.h"
LoggerManager *LoggerManager::mInstance = nullptr;
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
	}

	return *mLogs[name];
}

void LoggerManager::Release()
{
	delete mInstance;
	mInstance = nullptr;
}

LoggerManager::LoggerManager()
{

}

void LoggerManager::SetLogFolder( std::string folder )
{
	mLogFolder = folder;
}

LoggerManager & LoggerManager::Instance()
{
	if (mInstance == nullptr)
	{
		mInstance = new LoggerManager();
	}
	return *mInstance;
}

LoggerManager::~LoggerManager()
{
	mLogs.clear();
}
