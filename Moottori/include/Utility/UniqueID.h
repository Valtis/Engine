#pragma once
#include <cstddef>

 

class UniqueID
{
public:
	UniqueID();

	UniqueID(unsigned int id);
	~UniqueID();

	bool operator==(const UniqueID &other) const
	{
		return mID == other.mID;
	}

	unsigned int GetID() const { return mID; }

private:
	static unsigned int mLastID;
	unsigned int mID;
};


class UniqueIDHashFunction
{
public:
    std::size_t operator()(UniqueID const& id) const 
    {
		return id.GetID();
    }
};