#pragma once
#include "Logger.h"
#include <unordered_map>
#include <memory>

class LoggerManager
{
public:

	~LoggerManager();
	
	static LoggerManager &Instance();

	static void SetLogFolder(std::string folder);

	static void Release();

	Logger &GetLog(std::string name);


private:
	LoggerManager();

	std::string GetFullName( const std::string &name );
	static LoggerManager *mInstance;
	static std::string mLogFolder;
	std::unordered_map<std::string, std::unique_ptr<Logger>> mLogs;
};