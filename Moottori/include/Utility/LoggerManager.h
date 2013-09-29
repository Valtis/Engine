#pragma once
#include "Logger.h"
#include <unordered_map>
#include <memory>
#include "Utility/Defines.h"

class LoggerManager
{
public:	
	static void SetLogFolder(std::string folder);
	static void Release();
	static Logger &GetLog(std::string name);

#if !defined _MSC_VER || _MSC_VER >= 1800 
	LoggerManager(const LoggerManager &) = delete;
	LoggerManager &operator=(const LoggerManager &) = delete;
#else
private:
	LoggerManager(const LoggerManager &);
	LoggerManager &operator=(const LoggerManager &);
public:
#endif


private:
	LoggerManager();
	~LoggerManager();

	static std::string GetFullName( const std::string &name );

	static std::string mLogFolder;
	static std::unordered_map<std::string, std::unique_ptr<Logger>> mLogs;
};