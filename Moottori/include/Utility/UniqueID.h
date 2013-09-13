#pragma once
#include <cstddef>

#include <set>

class UniqueID
{
public:
	UniqueID();

	UniqueID(int id);
	~UniqueID();

	bool operator==(const UniqueID &other) const
	{
		return mID == other.mID;
	}

	bool operator==(const int &val) const
	{
		return mID == val;
	}
	
	unsigned int AsInt() const { return mID; }

private:
	std::set<int> mUsedIDs;
	static int mLastID;
	int mID;
};


class UniqueIDHashFunction
{
public:
    std::size_t operator()(UniqueID const& id) const 
    {
		return id.AsInt();
    }
};