#pragma once
#include "Utility/Enumerations.h"
#include <utility>
#include <vector>
class Controller
{
public:
	Controller() { }
	virtual ~Controller() { }
	virtual std::vector<std::pair<int, UIEventState>> HandleInput() = 0;
	
#if !defined _MSC_VER || _MSC_VER >= 1800 
	Controller(const Controller &) = delete;
	Controller &operator=(const Controller &) = delete;
#else
private:
	Controller(const Controller &);
	Controller &operator=(const Controller &);
public:
#endif


};