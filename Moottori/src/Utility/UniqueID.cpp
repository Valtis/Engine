#include "Utility/UniqueID.h"
#include <utility>
#include <stdexcept>
int UniqueID::mLastID = 0;
std::set<int> UniqueID::mUsedIDs;


UniqueID::UniqueID()
{
	mID = mLastID++;
	mUsedIDs.insert(mID);
}

UniqueID::UniqueID(int id)
{
	if (mUsedIDs.count(id) != 0)
	{
		throw std::logic_error("Attempting to assign value to UniqueID that is not unique");
	}

	mID = id;
	if (id >= mLastID)
	{
		mLastID = id + 1;
	}
}


UniqueID::~UniqueID()
{
}