#pragma once
#include "Logger.h"
#include <unordered_map>
#include <memory>

class LoggerManager
{
public:

	~LoggerManager() { mLogs.clear(); }
	
	static LoggerManager &Instance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new LoggerManager();
		}
		return *mInstance;
	}

	static void SetLogFolder(std::String folder)
	{
		mLogFolder = folder;
	}

	static void Release()  
	{
		delete mInstance;
		mInstance = nullptr;
	}

	Logger &GetLog(std::string name, LogLevel level)
	{
		name = mLogFolder + "/" + name;
		if (mLogs.count(name) == 0)
		{
			mLogs[name].Open(name);
			mLogs[name].SetLoggingLevel(level);
			mLogs[name].AddTimeStamps(true);
		}

		return mLogs[name];
	}

private:
	LoggerManager() { }
	
	static LoggerManager *mInstance;
	static std::string mLogFolder;
	std::unordered_map<std::string, Logger> mLogs;
};